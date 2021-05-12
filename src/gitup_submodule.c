#include "submodule.h"

#include "git2/config.h"
#include "git2/sys/config.h"
#include "git2/types.h"
#include "git2/index.h"
#include "buffer.h"
#include "buf_text.h"
#include "vector.h"
#include "posix.h"
#include "config_backend.h"
#include "config.h"
#include "repository.h"
#include "tree.h"
#include "iterator.h"
#include "path.h"
#include "index.h"
#include "worktree.h"
#include "clone.h"

/**
 * Retains a submodule
 *
 * @param submodule Submodule object
 */
// GIT_EXTERN(void) git_submodule_retain(git_submodule *submodule);
void gitup_submodule_retain(git_submodule *sm)
{
	assert(sm);
	GIT_REFCOUNT_INC(sm);
}

