#include "config.h"

#include "git2/config.h"
#include "git2/sys/config.h"

#include "buf_text.h"
#include "config_backend.h"
#include "regexp.h"
#include "sysdir.h"
#include "transaction.h"
#include "vector.h"
#if GIT_WIN32
# include <windows.h>
#endif

#include <ctype.h>

int git_config_find_local(git_repository *repo, git_buf *path)
{
	assert(repo);

	git_buf_sanitize(path);
	if (git_buf_joinpath(path, repo->gitdir, GIT_CONFIG_FILENAME_INREPO) < 0)
    return -1;

	if (!git_path_exists(path->ptr)) {
		giterr_set(GITERR_OS, "The config file '%s' doesn't exist", path->ptr);
		return GIT_ENOTFOUND;
	}

	return 0;
}
