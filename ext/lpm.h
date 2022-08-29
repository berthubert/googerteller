/*
 * Copyright (c) 2016 Mindaugas Rasiukevicius <rmind at noxt eu>
 * All rights reserved.
 *
 * Use is subject to license terms, as specified in the LICENSE file.
 */

#ifndef _LPM_H_
#define _LPM_H_

__BEGIN_DECLS

typedef struct lpm lpm_t;
typedef void (*lpm_dtor_t)(void *, const void *, size_t, void *);

lpm_t *		lpm_create(void);
void		lpm_destroy(lpm_t *);
void		lpm_clear(lpm_t *, lpm_dtor_t, void *);

int		lpm_insert(lpm_t *, const void *, size_t, unsigned, void *);
int		lpm_remove(lpm_t *, const void *, size_t, unsigned);
void *		lpm_lookup(lpm_t *, const void *, size_t);
void *		lpm_lookup_prefix(lpm_t *, const void *, size_t, unsigned);
int		lpm_strtobin(const char *, void *, size_t *, unsigned *);

__END_DECLS

#endif
