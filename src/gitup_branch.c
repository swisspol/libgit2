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
	return git_branch_upstream_name(out, repo, refname);
}

/// Ignore this method.
/// This method should be removed.
int gitup_branch_upstream_name_from_merge_remote_names(git_buf *out, git_repository *repo, const char *remote_name, const char *merge_name) {
	return -1;
	int error = -1;
	git_remote *remote = NULL;
	const git_refspec *refspec;
    git_buf buf = GIT_BUF_INIT;
    
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

/// Actually, you have to use `git_branch_upstream_name`.
/// This method is dup of method `retrieve_upstream_configuration` in `branch.c`
static int gitup_retrieve_upstream_configuration(
	git_buf *out,
	const git_config *config,
	const char *canonical_branch_name,
	const char *format)
{
	git_buf buf = GIT_BUF_INIT;
	int error;

	if (git_buf_printf(&buf, format,
		canonical_branch_name + strlen(GIT_REFS_HEADS_DIR)) < 0)
			return -1;

	error = git_config_get_string_buf(out, config, git_buf_cstr(&buf));
	git_buf_dispose(&buf);
	return error;
}

static int gitup_branch_upstream_format(git_buf *buf, git_repository *repo, const char *refname, const char *format) {
    int error;
    git_config *config;
    if ((error = git_repository_config_snapshot(&config, repo)) < 0)
        return error;
    return gitup_retrieve_upstream_configuration(buf, config, refname, format);
}

/// May be in PR.
int gitup_branch_upstream_remote(git_buf *buf, git_repository *repo, const char *refname)
{
	return gitup_branch_upstream_format(buf, repo, refname, "branch.%s.remote");
}

int gitup_branch_upstream_merge(git_buf *buf, git_repository *repo, const char *refname)
{
	return gitup_branch_upstream_format(buf, repo, refname, "branch.%s.merge");
}
