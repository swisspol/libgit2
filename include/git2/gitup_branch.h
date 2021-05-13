#include "common.h"
#include "oid.h"
#include "types.h"

/**
 * @file git2/branch.h
 * @brief Git branch parsing routines
 * @defgroup git_branch Git branch management
 * @ingroup Git
 * @{
 */
GIT_BEGIN_DECL
// PATCH
/// This method can be ignored. Use `gitup_branch_upstream_name` instead.
GIT_EXTERN(int) gitup_branch_upstream_name_from_merge_remote_names(git_buf *out, git_repository *repo, const char *remote_name, const char *merge_name);
/// Use this method.
GIT_EXTERN(int) gitup_branch_upstream_name(git_buf *out, git_repository *repo, const char *refname);

// PATCH
/// These methods could be (?) replaced by `gitup_branch_upstream_name` also.
GIT_EXTERN(int) gitup_branch_upstream_remote(git_buf *buf, git_repository *repo, const char *refname);
GIT_EXTERN(int) gitup_branch_upstream_merge(git_buf *buf, git_repository *repo, const char *refname);

/** @} */
GIT_END_DECL
