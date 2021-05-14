/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */

#include "git2/gitup_repository.h"
#include "git2/repository.h"
#include "repository.h"

#include <ctype.h>

#include "git2/object.h"
#include "git2/sys/repository.h"

#include "common.h"
#include "commit.h"
#include "tag.h"
#include "blob.h"
#include "futils.h"
#include "sysdir.h"
#include "filebuf.h"
#include "index.h"
#include "config.h"
#include "refs.h"
#include "filter.h"
#include "odb.h"
#include "refdb.h"
#include "remote.h"
#include "merge.h"
#include "diff_driver.h"
#include "annotated_commit.h"
#include "submodule.h"
#include "worktree.h"

#include "strmap.h"

#ifdef GIT_WIN32
# include "win32/w32_util.h"
#endif

int git_repository_update_gitlink(
	git_repository *repo,
	int use_relative_path)
{
	int error;
	const char *workdir = git_repository_workdir(repo);
	int update_gitlink = 1;

	if ((error = git_futils_mkdir(workdir, 0777, GIT_MKDIR_PATH | GIT_MKDIR_VERIFY_DIR)) < 0)
		return error;

	if ((error = git_repository_set_workdir(repo, workdir, update_gitlink)) < 0 )
		return error;

	return 0;
}
