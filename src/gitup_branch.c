#include "branch.h"

#include "commit.h"
#include "tag.h"
#include "config.h"
#include "refspec.h"
#include "refs.h"
#include "remote.h"
#include "annotated_commit.h"
#include "worktree.h"

#include "git2/branch.h"

int gitup_branch_upstream_name(git_buf *out, git_repository *repo, const char *refname) {
	git_branch_upstream_name(out, repo, refname);
}

/// Ignore this method.
int gitup_branch_upstream_name_from_merge_remote_names(git_buf *out, git_repository *repo, const char *remote_name, const char *merge_name) {
	return -1;
	git_buf buf = GIT_BUF_INIT;
	int error = -1;
	git_remote *remote = NULL;
	const git_refspec *refspec;

	assert(out && remote_name && merge_name);

	git_buf_sanitize(out);

	if (strcmp(".", remote_name) != 0) {
		if ((error = git_remote_lookup(&remote, repo, remote_name)) < 0)
			goto cleanup;

		refspec = git_remote__matching_refspec(remote, merge_name);
		if (!refspec) {
			error = GIT_ENOTFOUND;
			goto cleanup;
		}

		if (git_refspec_transform(&buf, refspec, merge_name) < 0)
			goto cleanup;
	} else
		if (git_buf_set(&buf, merge_name, strlen(merge_name)) < 0)
			goto cleanup;

	error = git_buf_set(out, git_buf_cstr(&buf), git_buf_len(&buf));

cleanup:
	git_remote_free(remote);
	git_buf_free(&buf);
	return error;
}

