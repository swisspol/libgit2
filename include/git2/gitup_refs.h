#include "refs.h"

GIT_BEGIN_DECL

/**
 * Create a virtual direct reference.
 *
 * @param out Pointer to the newly created reference
 * @param repo Repository where that reference virtually lives
 * @param name The name of the reference
 * @param id The object id pointed to by the reference
 * @return 0 on success or an error code
 */
GIT_EXTERN(int) gitup_reference_create_virtual(git_reference **out, git_repository *repo, const char *name, const git_oid *id);

/**
 * Create a virtual symbolic reference.
 *
 * @param out Pointer to the newly created reference
 * @param repo Repository where that reference virtually lives
 * @param name The name of the reference
 * @param target The target of the reference
 * @return 0 on success or an error code
 */
GIT_EXTERN(int) gitup_reference_symbolic_create_virtual(git_reference **out, git_repository *repo, const char *name, const char *target);

GIT_END_DECL