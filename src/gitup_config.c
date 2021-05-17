#include "config.h"
#include "git2/config.h"
#include "git2/gitup_config.h"
#include "vector.h"

int gitup_config_find_local(git_repository *repo, git_buf *path)
{
	assert(repo);

	git_buf_sanitize(path);
	if (git_buf_joinpath(path, repo->gitdir, GIT_CONFIG_FILENAME_INREPO) < 0)
		return -1;

	if (!git_path_exists(path->ptr)) {
		git_error_set(GIT_ERROR_OS, "The config file '%s' doesn't exist", path->ptr);
		return GIT_ENOTFOUND;
	}

	return 0;
}
