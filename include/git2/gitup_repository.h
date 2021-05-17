#include "repository.h"
#include "common.h"
#include "types.h"
#include "oid.h"
#include "buffer.h"

/**
 * @file git2/repository.h
 * @brief Git repository management routines
 * @defgroup git_repository Git repository management routines
 * @ingroup Git
 * @{
 */
GIT_BEGIN_DECL

/**
 * Update or rewrite the gitlink in the workdir
 */
GIT_EXTERN(int) gitup_repository_update_gitlink(
    git_repository *repo, int use_relative_path);

/** @} */
GIT_END_DECL
