#include "refs.h"
#include "git2/refs.h"
#include "git2/gitup_refs.h"
#include "repository.h"
#include "filebuf.h"
#include "pack.h"
#include "reflog.h"
#include "refdb.h"

#include <git2/oid.h>
#include <git2/sys/refs.h>

int gitup_reference_create_virtual(
    git_reference **ref_out,
    git_repository *repo,
    const char *name,
    const git_oid *id)
{
    int error;
    git_refdb *refdb;
    git_reference *ref;

    assert(ref_out && repo && name && id);

    if ((error = git_repository_refdb__weakptr(&refdb, repo)) < 0)
        return error;

    ref = git_reference__alloc(name, id, NULL);
    GIT_REFCOUNT_INC(refdb);
    ref->db = refdb;

    *ref_out = ref;
    return 0;
}

int gitup_reference_symbolic_create_virtual(
    git_reference **ref_out,
    git_repository *repo,
    const char *name,
    const char *target)
{
    int error;
    git_refdb *refdb;
    git_reference *ref;

    assert(ref_out && repo && name && target);

    if ((error = git_repository_refdb__weakptr(&refdb, repo)) < 0)
        return error;

    ref = git_reference__alloc_symbolic(name, target);
    GIT_REFCOUNT_INC(refdb);
    ref->db = refdb;

    *ref_out = ref;
    return 0;
}
