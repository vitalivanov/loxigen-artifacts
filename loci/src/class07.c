/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_ipv6_nd_target_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80003e10); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_ipv6_nd_target of_oxm_ipv6_nd_target
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_ipv6_nd_target_push_wire_values(of_oxm_ipv6_nd_target_t *obj)
{

    of_oxm_ipv6_nd_target_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_ipv6_nd_target object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_ipv6_nd_target
 */

of_oxm_ipv6_nd_target_t *
of_oxm_ipv6_nd_target_new(of_version_t version)
{
    of_oxm_ipv6_nd_target_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_IPV6_ND_TARGET] + of_object_extra_len[version][OF_OXM_IPV6_ND_TARGET];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_ipv6_nd_target_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_ipv6_nd_target_init(obj, version, bytes, 0);

    if (of_oxm_ipv6_nd_target_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_ipv6_nd_target.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_ipv6_nd_target_init(of_oxm_ipv6_nd_target_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_IPV6_ND_TARGET] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_IPV6_ND_TARGET] + of_object_extra_len[version][OF_OXM_IPV6_ND_TARGET];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_IPV6_ND_TARGET;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_ipv6_nd_target_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_ipv6_nd_target.
 * @param obj Pointer to an object of type of_oxm_ipv6_nd_target.
 * @param value Pointer to the child object of type
 * of_ipv6_t to be filled out.
 *
 */
void
of_oxm_ipv6_nd_target_value_get(
    of_oxm_ipv6_nd_target_t *obj,
    of_ipv6_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_IPV6_ND_TARGET);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_ipv6_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_ipv6_nd_target.
 * @param obj Pointer to an object of type of_oxm_ipv6_nd_target.
 * @param value The value to write into the object
 */
void
of_oxm_ipv6_nd_target_value_set(
    of_oxm_ipv6_nd_target_t *obj,
    of_ipv6_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_IPV6_ND_TARGET);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_ipv6_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_ipv6_nd_target_masked_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80003f20); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_ipv6_nd_target_masked of_oxm_ipv6_nd_target_masked
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_ipv6_nd_target_masked_push_wire_values(of_oxm_ipv6_nd_target_masked_t *obj)
{

    of_oxm_ipv6_nd_target_masked_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_ipv6_nd_target_masked object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_ipv6_nd_target_masked
 */

of_oxm_ipv6_nd_target_masked_t *
of_oxm_ipv6_nd_target_masked_new(of_version_t version)
{
    of_oxm_ipv6_nd_target_masked_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_IPV6_ND_TARGET_MASKED] + of_object_extra_len[version][OF_OXM_IPV6_ND_TARGET_MASKED];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_ipv6_nd_target_masked_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_ipv6_nd_target_masked_init(obj, version, bytes, 0);

    if (of_oxm_ipv6_nd_target_masked_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_ipv6_nd_target_masked.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_ipv6_nd_target_masked_init(of_oxm_ipv6_nd_target_masked_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_IPV6_ND_TARGET_MASKED] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_IPV6_ND_TARGET_MASKED] + of_object_extra_len[version][OF_OXM_IPV6_ND_TARGET_MASKED];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_IPV6_ND_TARGET_MASKED;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_ipv6_nd_target_masked_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_ipv6_nd_target_masked.
 * @param obj Pointer to an object of type of_oxm_ipv6_nd_target_masked.
 * @param value Pointer to the child object of type
 * of_ipv6_t to be filled out.
 *
 */
void
of_oxm_ipv6_nd_target_masked_value_get(
    of_oxm_ipv6_nd_target_masked_t *obj,
    of_ipv6_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_IPV6_ND_TARGET_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_ipv6_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_ipv6_nd_target_masked.
 * @param obj Pointer to an object of type of_oxm_ipv6_nd_target_masked.
 * @param value The value to write into the object
 */
void
of_oxm_ipv6_nd_target_masked_value_set(
    of_oxm_ipv6_nd_target_masked_t *obj,
    of_ipv6_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_IPV6_ND_TARGET_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_ipv6_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Get value_mask from an object of type of_oxm_ipv6_nd_target_masked.
 * @param obj Pointer to an object of type of_oxm_ipv6_nd_target_masked.
 * @param value_mask Pointer to the child object of type
 * of_ipv6_t to be filled out.
 *
 */
void
of_oxm_ipv6_nd_target_masked_value_mask_get(
    of_oxm_ipv6_nd_target_masked_t *obj,
    of_ipv6_t *value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_IPV6_ND_TARGET_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 20;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_ipv6_get(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value_mask in an object of type of_oxm_ipv6_nd_target_masked.
 * @param obj Pointer to an object of type of_oxm_ipv6_nd_target_masked.
 * @param value_mask The value to write into the object
 */
void
of_oxm_ipv6_nd_target_masked_value_mask_set(
    of_oxm_ipv6_nd_target_masked_t *obj,
    of_ipv6_t value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_IPV6_ND_TARGET_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 20;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_ipv6_set(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_ipv6_nd_tll_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80004206); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_ipv6_nd_tll of_oxm_ipv6_nd_tll
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_ipv6_nd_tll_push_wire_values(of_oxm_ipv6_nd_tll_t *obj)
{

    of_oxm_ipv6_nd_tll_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_ipv6_nd_tll object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_ipv6_nd_tll
 */

of_oxm_ipv6_nd_tll_t *
of_oxm_ipv6_nd_tll_new(of_version_t version)
{
    of_oxm_ipv6_nd_tll_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_IPV6_ND_TLL] + of_object_extra_len[version][OF_OXM_IPV6_ND_TLL];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_ipv6_nd_tll_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_ipv6_nd_tll_init(obj, version, bytes, 0);

    if (of_oxm_ipv6_nd_tll_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_ipv6_nd_tll.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_ipv6_nd_tll_init(of_oxm_ipv6_nd_tll_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_IPV6_ND_TLL] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_IPV6_ND_TLL] + of_object_extra_len[version][OF_OXM_IPV6_ND_TLL];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_IPV6_ND_TLL;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_ipv6_nd_tll_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_ipv6_nd_tll.
 * @param obj Pointer to an object of type of_oxm_ipv6_nd_tll.
 * @param value Pointer to the child object of type
 * of_mac_addr_t to be filled out.
 *
 */
void
of_oxm_ipv6_nd_tll_value_get(
    of_oxm_ipv6_nd_tll_t *obj,
    of_mac_addr_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_IPV6_ND_TLL);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_mac_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_ipv6_nd_tll.
 * @param obj Pointer to an object of type of_oxm_ipv6_nd_tll.
 * @param value The value to write into the object
 */
void
of_oxm_ipv6_nd_tll_value_set(
    of_oxm_ipv6_nd_tll_t *obj,
    of_mac_addr_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_IPV6_ND_TLL);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_mac_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_ipv6_nd_tll_masked_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x8000430c); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_ipv6_nd_tll_masked of_oxm_ipv6_nd_tll_masked
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_ipv6_nd_tll_masked_push_wire_values(of_oxm_ipv6_nd_tll_masked_t *obj)
{

    of_oxm_ipv6_nd_tll_masked_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_ipv6_nd_tll_masked object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_ipv6_nd_tll_masked
 */

of_oxm_ipv6_nd_tll_masked_t *
of_oxm_ipv6_nd_tll_masked_new(of_version_t version)
{
    of_oxm_ipv6_nd_tll_masked_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_IPV6_ND_TLL_MASKED] + of_object_extra_len[version][OF_OXM_IPV6_ND_TLL_MASKED];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_ipv6_nd_tll_masked_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_ipv6_nd_tll_masked_init(obj, version, bytes, 0);

    if (of_oxm_ipv6_nd_tll_masked_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_ipv6_nd_tll_masked.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_ipv6_nd_tll_masked_init(of_oxm_ipv6_nd_tll_masked_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_IPV6_ND_TLL_MASKED] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_IPV6_ND_TLL_MASKED] + of_object_extra_len[version][OF_OXM_IPV6_ND_TLL_MASKED];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_IPV6_ND_TLL_MASKED;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_ipv6_nd_tll_masked_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_ipv6_nd_tll_masked.
 * @param obj Pointer to an object of type of_oxm_ipv6_nd_tll_masked.
 * @param value Pointer to the child object of type
 * of_mac_addr_t to be filled out.
 *
 */
void
of_oxm_ipv6_nd_tll_masked_value_get(
    of_oxm_ipv6_nd_tll_masked_t *obj,
    of_mac_addr_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_IPV6_ND_TLL_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_mac_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_ipv6_nd_tll_masked.
 * @param obj Pointer to an object of type of_oxm_ipv6_nd_tll_masked.
 * @param value The value to write into the object
 */
void
of_oxm_ipv6_nd_tll_masked_value_set(
    of_oxm_ipv6_nd_tll_masked_t *obj,
    of_mac_addr_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_IPV6_ND_TLL_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_mac_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Get value_mask from an object of type of_oxm_ipv6_nd_tll_masked.
 * @param obj Pointer to an object of type of_oxm_ipv6_nd_tll_masked.
 * @param value_mask Pointer to the child object of type
 * of_mac_addr_t to be filled out.
 *
 */
void
of_oxm_ipv6_nd_tll_masked_value_mask_get(
    of_oxm_ipv6_nd_tll_masked_t *obj,
    of_mac_addr_t *value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_IPV6_ND_TLL_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 10;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_mac_get(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value_mask in an object of type of_oxm_ipv6_nd_tll_masked.
 * @param obj Pointer to an object of type of_oxm_ipv6_nd_tll_masked.
 * @param value_mask The value to write into the object
 */
void
of_oxm_ipv6_nd_tll_masked_value_mask_set(
    of_oxm_ipv6_nd_tll_masked_t *obj,
    of_mac_addr_t value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_IPV6_ND_TLL_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 10;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_mac_set(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_ipv6_src_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80003410); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_ipv6_src of_oxm_ipv6_src
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_ipv6_src_push_wire_values(of_oxm_ipv6_src_t *obj)
{

    of_oxm_ipv6_src_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_ipv6_src object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_ipv6_src
 */

of_oxm_ipv6_src_t *
of_oxm_ipv6_src_new(of_version_t version)
{
    of_oxm_ipv6_src_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_IPV6_SRC] + of_object_extra_len[version][OF_OXM_IPV6_SRC];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_ipv6_src_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_ipv6_src_init(obj, version, bytes, 0);

    if (of_oxm_ipv6_src_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_ipv6_src.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_ipv6_src_init(of_oxm_ipv6_src_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_IPV6_SRC] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_IPV6_SRC] + of_object_extra_len[version][OF_OXM_IPV6_SRC];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_IPV6_SRC;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_ipv6_src_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_ipv6_src.
 * @param obj Pointer to an object of type of_oxm_ipv6_src.
 * @param value Pointer to the child object of type
 * of_ipv6_t to be filled out.
 *
 */
void
of_oxm_ipv6_src_value_get(
    of_oxm_ipv6_src_t *obj,
    of_ipv6_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_IPV6_SRC);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_ipv6_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_ipv6_src.
 * @param obj Pointer to an object of type of_oxm_ipv6_src.
 * @param value The value to write into the object
 */
void
of_oxm_ipv6_src_value_set(
    of_oxm_ipv6_src_t *obj,
    of_ipv6_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_IPV6_SRC);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_ipv6_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_ipv6_src_masked_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80003520); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_ipv6_src_masked of_oxm_ipv6_src_masked
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_ipv6_src_masked_push_wire_values(of_oxm_ipv6_src_masked_t *obj)
{

    of_oxm_ipv6_src_masked_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_ipv6_src_masked object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_ipv6_src_masked
 */

of_oxm_ipv6_src_masked_t *
of_oxm_ipv6_src_masked_new(of_version_t version)
{
    of_oxm_ipv6_src_masked_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_IPV6_SRC_MASKED] + of_object_extra_len[version][OF_OXM_IPV6_SRC_MASKED];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_ipv6_src_masked_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_ipv6_src_masked_init(obj, version, bytes, 0);

    if (of_oxm_ipv6_src_masked_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_ipv6_src_masked.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_ipv6_src_masked_init(of_oxm_ipv6_src_masked_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_IPV6_SRC_MASKED] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_IPV6_SRC_MASKED] + of_object_extra_len[version][OF_OXM_IPV6_SRC_MASKED];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_IPV6_SRC_MASKED;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_ipv6_src_masked_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_ipv6_src_masked.
 * @param obj Pointer to an object of type of_oxm_ipv6_src_masked.
 * @param value Pointer to the child object of type
 * of_ipv6_t to be filled out.
 *
 */
void
of_oxm_ipv6_src_masked_value_get(
    of_oxm_ipv6_src_masked_t *obj,
    of_ipv6_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_IPV6_SRC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_ipv6_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_ipv6_src_masked.
 * @param obj Pointer to an object of type of_oxm_ipv6_src_masked.
 * @param value The value to write into the object
 */
void
of_oxm_ipv6_src_masked_value_set(
    of_oxm_ipv6_src_masked_t *obj,
    of_ipv6_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_IPV6_SRC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_ipv6_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Get value_mask from an object of type of_oxm_ipv6_src_masked.
 * @param obj Pointer to an object of type of_oxm_ipv6_src_masked.
 * @param value_mask Pointer to the child object of type
 * of_ipv6_t to be filled out.
 *
 */
void
of_oxm_ipv6_src_masked_value_mask_get(
    of_oxm_ipv6_src_masked_t *obj,
    of_ipv6_t *value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_IPV6_SRC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 20;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_ipv6_get(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value_mask in an object of type of_oxm_ipv6_src_masked.
 * @param obj Pointer to an object of type of_oxm_ipv6_src_masked.
 * @param value_mask The value to write into the object
 */
void
of_oxm_ipv6_src_masked_value_mask_set(
    of_oxm_ipv6_src_masked_t *obj,
    of_ipv6_t value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_IPV6_SRC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 20;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_ipv6_set(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_metadata_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80000408); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_metadata of_oxm_metadata
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_metadata_push_wire_values(of_oxm_metadata_t *obj)
{

    of_oxm_metadata_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_metadata object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_metadata
 */

of_oxm_metadata_t *
of_oxm_metadata_new(of_version_t version)
{
    of_oxm_metadata_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_METADATA] + of_object_extra_len[version][OF_OXM_METADATA];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_metadata_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_metadata_init(obj, version, bytes, 0);

    if (of_oxm_metadata_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_metadata.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_metadata_init(of_oxm_metadata_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_METADATA] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_METADATA] + of_object_extra_len[version][OF_OXM_METADATA];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_METADATA;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_metadata_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_metadata.
 * @param obj Pointer to an object of type of_oxm_metadata.
 * @param value Pointer to the child object of type
 * uint64_t to be filled out.
 *
 */
void
of_oxm_metadata_value_get(
    of_oxm_metadata_t *obj,
    uint64_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_METADATA);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u64_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_metadata.
 * @param obj Pointer to an object of type of_oxm_metadata.
 * @param value The value to write into the object
 */
void
of_oxm_metadata_value_set(
    of_oxm_metadata_t *obj,
    uint64_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_METADATA);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u64_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_metadata_masked_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80000510); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_metadata_masked of_oxm_metadata_masked
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_metadata_masked_push_wire_values(of_oxm_metadata_masked_t *obj)
{

    of_oxm_metadata_masked_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_metadata_masked object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_metadata_masked
 */

of_oxm_metadata_masked_t *
of_oxm_metadata_masked_new(of_version_t version)
{
    of_oxm_metadata_masked_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_METADATA_MASKED] + of_object_extra_len[version][OF_OXM_METADATA_MASKED];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_metadata_masked_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_metadata_masked_init(obj, version, bytes, 0);

    if (of_oxm_metadata_masked_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_metadata_masked.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_metadata_masked_init(of_oxm_metadata_masked_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_METADATA_MASKED] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_METADATA_MASKED] + of_object_extra_len[version][OF_OXM_METADATA_MASKED];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_METADATA_MASKED;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_metadata_masked_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_metadata_masked.
 * @param obj Pointer to an object of type of_oxm_metadata_masked.
 * @param value Pointer to the child object of type
 * uint64_t to be filled out.
 *
 */
void
of_oxm_metadata_masked_value_get(
    of_oxm_metadata_masked_t *obj,
    uint64_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_METADATA_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u64_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_metadata_masked.
 * @param obj Pointer to an object of type of_oxm_metadata_masked.
 * @param value The value to write into the object
 */
void
of_oxm_metadata_masked_value_set(
    of_oxm_metadata_masked_t *obj,
    uint64_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_METADATA_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u64_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Get value_mask from an object of type of_oxm_metadata_masked.
 * @param obj Pointer to an object of type of_oxm_metadata_masked.
 * @param value_mask Pointer to the child object of type
 * uint64_t to be filled out.
 *
 */
void
of_oxm_metadata_masked_value_mask_get(
    of_oxm_metadata_masked_t *obj,
    uint64_t *value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_METADATA_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 12;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u64_get(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value_mask in an object of type of_oxm_metadata_masked.
 * @param obj Pointer to an object of type of_oxm_metadata_masked.
 * @param value_mask The value to write into the object
 */
void
of_oxm_metadata_masked_value_mask_set(
    of_oxm_metadata_masked_t *obj,
    uint64_t value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_METADATA_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 12;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u64_set(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_mpls_label_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80004404); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_mpls_label of_oxm_mpls_label
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_mpls_label_push_wire_values(of_oxm_mpls_label_t *obj)
{

    of_oxm_mpls_label_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_mpls_label object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_mpls_label
 */

of_oxm_mpls_label_t *
of_oxm_mpls_label_new(of_version_t version)
{
    of_oxm_mpls_label_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_MPLS_LABEL] + of_object_extra_len[version][OF_OXM_MPLS_LABEL];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_mpls_label_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_mpls_label_init(obj, version, bytes, 0);

    if (of_oxm_mpls_label_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_mpls_label.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_mpls_label_init(of_oxm_mpls_label_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_MPLS_LABEL] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_MPLS_LABEL] + of_object_extra_len[version][OF_OXM_MPLS_LABEL];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_MPLS_LABEL;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_mpls_label_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_mpls_label.
 * @param obj Pointer to an object of type of_oxm_mpls_label.
 * @param value Pointer to the child object of type
 * uint32_t to be filled out.
 *
 */
void
of_oxm_mpls_label_value_get(
    of_oxm_mpls_label_t *obj,
    uint32_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_MPLS_LABEL);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u32_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_mpls_label.
 * @param obj Pointer to an object of type of_oxm_mpls_label.
 * @param value The value to write into the object
 */
void
of_oxm_mpls_label_value_set(
    of_oxm_mpls_label_t *obj,
    uint32_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_MPLS_LABEL);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u32_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_mpls_label_masked_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80004508); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_mpls_label_masked of_oxm_mpls_label_masked
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_mpls_label_masked_push_wire_values(of_oxm_mpls_label_masked_t *obj)
{

    of_oxm_mpls_label_masked_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_mpls_label_masked object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_mpls_label_masked
 */

of_oxm_mpls_label_masked_t *
of_oxm_mpls_label_masked_new(of_version_t version)
{
    of_oxm_mpls_label_masked_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_MPLS_LABEL_MASKED] + of_object_extra_len[version][OF_OXM_MPLS_LABEL_MASKED];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_mpls_label_masked_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_mpls_label_masked_init(obj, version, bytes, 0);

    if (of_oxm_mpls_label_masked_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_mpls_label_masked.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_mpls_label_masked_init(of_oxm_mpls_label_masked_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_MPLS_LABEL_MASKED] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_MPLS_LABEL_MASKED] + of_object_extra_len[version][OF_OXM_MPLS_LABEL_MASKED];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_MPLS_LABEL_MASKED;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_mpls_label_masked_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_mpls_label_masked.
 * @param obj Pointer to an object of type of_oxm_mpls_label_masked.
 * @param value Pointer to the child object of type
 * uint32_t to be filled out.
 *
 */
void
of_oxm_mpls_label_masked_value_get(
    of_oxm_mpls_label_masked_t *obj,
    uint32_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_MPLS_LABEL_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u32_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_mpls_label_masked.
 * @param obj Pointer to an object of type of_oxm_mpls_label_masked.
 * @param value The value to write into the object
 */
void
of_oxm_mpls_label_masked_value_set(
    of_oxm_mpls_label_masked_t *obj,
    uint32_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_MPLS_LABEL_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u32_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Get value_mask from an object of type of_oxm_mpls_label_masked.
 * @param obj Pointer to an object of type of_oxm_mpls_label_masked.
 * @param value_mask Pointer to the child object of type
 * uint32_t to be filled out.
 *
 */
void
of_oxm_mpls_label_masked_value_mask_get(
    of_oxm_mpls_label_masked_t *obj,
    uint32_t *value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_MPLS_LABEL_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 8;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u32_get(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value_mask in an object of type of_oxm_mpls_label_masked.
 * @param obj Pointer to an object of type of_oxm_mpls_label_masked.
 * @param value_mask The value to write into the object
 */
void
of_oxm_mpls_label_masked_value_mask_set(
    of_oxm_mpls_label_masked_t *obj,
    uint32_t value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_MPLS_LABEL_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 8;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u32_set(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_mpls_tc_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80004601); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_mpls_tc of_oxm_mpls_tc
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_mpls_tc_push_wire_values(of_oxm_mpls_tc_t *obj)
{

    of_oxm_mpls_tc_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_mpls_tc object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_mpls_tc
 */

of_oxm_mpls_tc_t *
of_oxm_mpls_tc_new(of_version_t version)
{
    of_oxm_mpls_tc_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_MPLS_TC] + of_object_extra_len[version][OF_OXM_MPLS_TC];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_mpls_tc_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_mpls_tc_init(obj, version, bytes, 0);

    if (of_oxm_mpls_tc_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_mpls_tc.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_mpls_tc_init(of_oxm_mpls_tc_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_MPLS_TC] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_MPLS_TC] + of_object_extra_len[version][OF_OXM_MPLS_TC];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_MPLS_TC;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_mpls_tc_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_mpls_tc.
 * @param obj Pointer to an object of type of_oxm_mpls_tc.
 * @param value Pointer to the child object of type
 * uint8_t to be filled out.
 *
 */
void
of_oxm_mpls_tc_value_get(
    of_oxm_mpls_tc_t *obj,
    uint8_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_MPLS_TC);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u8_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_mpls_tc.
 * @param obj Pointer to an object of type of_oxm_mpls_tc.
 * @param value The value to write into the object
 */
void
of_oxm_mpls_tc_value_set(
    of_oxm_mpls_tc_t *obj,
    uint8_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_MPLS_TC);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u8_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_mpls_tc_masked_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80004702); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_mpls_tc_masked of_oxm_mpls_tc_masked
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_mpls_tc_masked_push_wire_values(of_oxm_mpls_tc_masked_t *obj)
{

    of_oxm_mpls_tc_masked_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_mpls_tc_masked object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_mpls_tc_masked
 */

of_oxm_mpls_tc_masked_t *
of_oxm_mpls_tc_masked_new(of_version_t version)
{
    of_oxm_mpls_tc_masked_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_MPLS_TC_MASKED] + of_object_extra_len[version][OF_OXM_MPLS_TC_MASKED];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_mpls_tc_masked_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_mpls_tc_masked_init(obj, version, bytes, 0);

    if (of_oxm_mpls_tc_masked_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_mpls_tc_masked.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_mpls_tc_masked_init(of_oxm_mpls_tc_masked_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_MPLS_TC_MASKED] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_MPLS_TC_MASKED] + of_object_extra_len[version][OF_OXM_MPLS_TC_MASKED];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_MPLS_TC_MASKED;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_mpls_tc_masked_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_mpls_tc_masked.
 * @param obj Pointer to an object of type of_oxm_mpls_tc_masked.
 * @param value Pointer to the child object of type
 * uint8_t to be filled out.
 *
 */
void
of_oxm_mpls_tc_masked_value_get(
    of_oxm_mpls_tc_masked_t *obj,
    uint8_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_MPLS_TC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u8_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_mpls_tc_masked.
 * @param obj Pointer to an object of type of_oxm_mpls_tc_masked.
 * @param value The value to write into the object
 */
void
of_oxm_mpls_tc_masked_value_set(
    of_oxm_mpls_tc_masked_t *obj,
    uint8_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_MPLS_TC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u8_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Get value_mask from an object of type of_oxm_mpls_tc_masked.
 * @param obj Pointer to an object of type of_oxm_mpls_tc_masked.
 * @param value_mask Pointer to the child object of type
 * uint8_t to be filled out.
 *
 */
void
of_oxm_mpls_tc_masked_value_mask_get(
    of_oxm_mpls_tc_masked_t *obj,
    uint8_t *value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_MPLS_TC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 5;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u8_get(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value_mask in an object of type of_oxm_mpls_tc_masked.
 * @param obj Pointer to an object of type of_oxm_mpls_tc_masked.
 * @param value_mask The value to write into the object
 */
void
of_oxm_mpls_tc_masked_value_mask_set(
    of_oxm_mpls_tc_masked_t *obj,
    uint8_t value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_MPLS_TC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 5;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u8_set(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_sctp_dst_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80002402); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_sctp_dst of_oxm_sctp_dst
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_sctp_dst_push_wire_values(of_oxm_sctp_dst_t *obj)
{

    of_oxm_sctp_dst_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_sctp_dst object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_sctp_dst
 */

of_oxm_sctp_dst_t *
of_oxm_sctp_dst_new(of_version_t version)
{
    of_oxm_sctp_dst_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_SCTP_DST] + of_object_extra_len[version][OF_OXM_SCTP_DST];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_sctp_dst_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_sctp_dst_init(obj, version, bytes, 0);

    if (of_oxm_sctp_dst_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_sctp_dst.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_sctp_dst_init(of_oxm_sctp_dst_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_SCTP_DST] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_SCTP_DST] + of_object_extra_len[version][OF_OXM_SCTP_DST];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_SCTP_DST;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_sctp_dst_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_sctp_dst.
 * @param obj Pointer to an object of type of_oxm_sctp_dst.
 * @param value Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_sctp_dst_value_get(
    of_oxm_sctp_dst_t *obj,
    uint16_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_SCTP_DST);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_sctp_dst.
 * @param obj Pointer to an object of type of_oxm_sctp_dst.
 * @param value The value to write into the object
 */
void
of_oxm_sctp_dst_value_set(
    of_oxm_sctp_dst_t *obj,
    uint16_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_SCTP_DST);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_sctp_dst_masked_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80002504); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_sctp_dst_masked of_oxm_sctp_dst_masked
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_sctp_dst_masked_push_wire_values(of_oxm_sctp_dst_masked_t *obj)
{

    of_oxm_sctp_dst_masked_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_sctp_dst_masked object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_sctp_dst_masked
 */

of_oxm_sctp_dst_masked_t *
of_oxm_sctp_dst_masked_new(of_version_t version)
{
    of_oxm_sctp_dst_masked_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_SCTP_DST_MASKED] + of_object_extra_len[version][OF_OXM_SCTP_DST_MASKED];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_sctp_dst_masked_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_sctp_dst_masked_init(obj, version, bytes, 0);

    if (of_oxm_sctp_dst_masked_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_sctp_dst_masked.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_sctp_dst_masked_init(of_oxm_sctp_dst_masked_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_SCTP_DST_MASKED] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_SCTP_DST_MASKED] + of_object_extra_len[version][OF_OXM_SCTP_DST_MASKED];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_SCTP_DST_MASKED;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_sctp_dst_masked_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_sctp_dst_masked.
 * @param obj Pointer to an object of type of_oxm_sctp_dst_masked.
 * @param value Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_sctp_dst_masked_value_get(
    of_oxm_sctp_dst_masked_t *obj,
    uint16_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_SCTP_DST_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_sctp_dst_masked.
 * @param obj Pointer to an object of type of_oxm_sctp_dst_masked.
 * @param value The value to write into the object
 */
void
of_oxm_sctp_dst_masked_value_set(
    of_oxm_sctp_dst_masked_t *obj,
    uint16_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_SCTP_DST_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Get value_mask from an object of type of_oxm_sctp_dst_masked.
 * @param obj Pointer to an object of type of_oxm_sctp_dst_masked.
 * @param value_mask Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_sctp_dst_masked_value_mask_get(
    of_oxm_sctp_dst_masked_t *obj,
    uint16_t *value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_SCTP_DST_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 6;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value_mask in an object of type of_oxm_sctp_dst_masked.
 * @param obj Pointer to an object of type of_oxm_sctp_dst_masked.
 * @param value_mask The value to write into the object
 */
void
of_oxm_sctp_dst_masked_value_mask_set(
    of_oxm_sctp_dst_masked_t *obj,
    uint16_t value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_SCTP_DST_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 6;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_sctp_src_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80002202); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_sctp_src of_oxm_sctp_src
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_sctp_src_push_wire_values(of_oxm_sctp_src_t *obj)
{

    of_oxm_sctp_src_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_sctp_src object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_sctp_src
 */

of_oxm_sctp_src_t *
of_oxm_sctp_src_new(of_version_t version)
{
    of_oxm_sctp_src_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_SCTP_SRC] + of_object_extra_len[version][OF_OXM_SCTP_SRC];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_sctp_src_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_sctp_src_init(obj, version, bytes, 0);

    if (of_oxm_sctp_src_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_sctp_src.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_sctp_src_init(of_oxm_sctp_src_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_SCTP_SRC] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_SCTP_SRC] + of_object_extra_len[version][OF_OXM_SCTP_SRC];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_SCTP_SRC;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_sctp_src_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_sctp_src.
 * @param obj Pointer to an object of type of_oxm_sctp_src.
 * @param value Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_sctp_src_value_get(
    of_oxm_sctp_src_t *obj,
    uint16_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_SCTP_SRC);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_sctp_src.
 * @param obj Pointer to an object of type of_oxm_sctp_src.
 * @param value The value to write into the object
 */
void
of_oxm_sctp_src_value_set(
    of_oxm_sctp_src_t *obj,
    uint16_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_SCTP_SRC);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_sctp_src_masked_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80002304); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_sctp_src_masked of_oxm_sctp_src_masked
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_sctp_src_masked_push_wire_values(of_oxm_sctp_src_masked_t *obj)
{

    of_oxm_sctp_src_masked_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_sctp_src_masked object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_sctp_src_masked
 */

of_oxm_sctp_src_masked_t *
of_oxm_sctp_src_masked_new(of_version_t version)
{
    of_oxm_sctp_src_masked_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_SCTP_SRC_MASKED] + of_object_extra_len[version][OF_OXM_SCTP_SRC_MASKED];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_sctp_src_masked_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_sctp_src_masked_init(obj, version, bytes, 0);

    if (of_oxm_sctp_src_masked_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_sctp_src_masked.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_sctp_src_masked_init(of_oxm_sctp_src_masked_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_SCTP_SRC_MASKED] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_SCTP_SRC_MASKED] + of_object_extra_len[version][OF_OXM_SCTP_SRC_MASKED];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_SCTP_SRC_MASKED;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_sctp_src_masked_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_sctp_src_masked.
 * @param obj Pointer to an object of type of_oxm_sctp_src_masked.
 * @param value Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_sctp_src_masked_value_get(
    of_oxm_sctp_src_masked_t *obj,
    uint16_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_SCTP_SRC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_sctp_src_masked.
 * @param obj Pointer to an object of type of_oxm_sctp_src_masked.
 * @param value The value to write into the object
 */
void
of_oxm_sctp_src_masked_value_set(
    of_oxm_sctp_src_masked_t *obj,
    uint16_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_SCTP_SRC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Get value_mask from an object of type of_oxm_sctp_src_masked.
 * @param obj Pointer to an object of type of_oxm_sctp_src_masked.
 * @param value_mask Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_sctp_src_masked_value_mask_get(
    of_oxm_sctp_src_masked_t *obj,
    uint16_t *value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_SCTP_SRC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 6;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value_mask in an object of type of_oxm_sctp_src_masked.
 * @param obj Pointer to an object of type of_oxm_sctp_src_masked.
 * @param value_mask The value to write into the object
 */
void
of_oxm_sctp_src_masked_value_mask_set(
    of_oxm_sctp_src_masked_t *obj,
    uint16_t value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_SCTP_SRC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 6;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_tcp_dst_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80001c02); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_tcp_dst of_oxm_tcp_dst
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_tcp_dst_push_wire_values(of_oxm_tcp_dst_t *obj)
{

    of_oxm_tcp_dst_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_tcp_dst object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_tcp_dst
 */

of_oxm_tcp_dst_t *
of_oxm_tcp_dst_new(of_version_t version)
{
    of_oxm_tcp_dst_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_TCP_DST] + of_object_extra_len[version][OF_OXM_TCP_DST];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_tcp_dst_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_tcp_dst_init(obj, version, bytes, 0);

    if (of_oxm_tcp_dst_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_tcp_dst.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_tcp_dst_init(of_oxm_tcp_dst_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_TCP_DST] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_TCP_DST] + of_object_extra_len[version][OF_OXM_TCP_DST];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_TCP_DST;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_tcp_dst_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_tcp_dst.
 * @param obj Pointer to an object of type of_oxm_tcp_dst.
 * @param value Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_tcp_dst_value_get(
    of_oxm_tcp_dst_t *obj,
    uint16_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_TCP_DST);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_tcp_dst.
 * @param obj Pointer to an object of type of_oxm_tcp_dst.
 * @param value The value to write into the object
 */
void
of_oxm_tcp_dst_value_set(
    of_oxm_tcp_dst_t *obj,
    uint16_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_TCP_DST);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_tcp_dst_masked_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80001d04); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_tcp_dst_masked of_oxm_tcp_dst_masked
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_tcp_dst_masked_push_wire_values(of_oxm_tcp_dst_masked_t *obj)
{

    of_oxm_tcp_dst_masked_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_tcp_dst_masked object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_tcp_dst_masked
 */

of_oxm_tcp_dst_masked_t *
of_oxm_tcp_dst_masked_new(of_version_t version)
{
    of_oxm_tcp_dst_masked_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_TCP_DST_MASKED] + of_object_extra_len[version][OF_OXM_TCP_DST_MASKED];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_tcp_dst_masked_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_tcp_dst_masked_init(obj, version, bytes, 0);

    if (of_oxm_tcp_dst_masked_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_tcp_dst_masked.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_tcp_dst_masked_init(of_oxm_tcp_dst_masked_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_TCP_DST_MASKED] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_TCP_DST_MASKED] + of_object_extra_len[version][OF_OXM_TCP_DST_MASKED];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_TCP_DST_MASKED;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_tcp_dst_masked_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_tcp_dst_masked.
 * @param obj Pointer to an object of type of_oxm_tcp_dst_masked.
 * @param value Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_tcp_dst_masked_value_get(
    of_oxm_tcp_dst_masked_t *obj,
    uint16_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_TCP_DST_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_tcp_dst_masked.
 * @param obj Pointer to an object of type of_oxm_tcp_dst_masked.
 * @param value The value to write into the object
 */
void
of_oxm_tcp_dst_masked_value_set(
    of_oxm_tcp_dst_masked_t *obj,
    uint16_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_TCP_DST_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Get value_mask from an object of type of_oxm_tcp_dst_masked.
 * @param obj Pointer to an object of type of_oxm_tcp_dst_masked.
 * @param value_mask Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_tcp_dst_masked_value_mask_get(
    of_oxm_tcp_dst_masked_t *obj,
    uint16_t *value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_TCP_DST_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 6;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value_mask in an object of type of_oxm_tcp_dst_masked.
 * @param obj Pointer to an object of type of_oxm_tcp_dst_masked.
 * @param value_mask The value to write into the object
 */
void
of_oxm_tcp_dst_masked_value_mask_set(
    of_oxm_tcp_dst_masked_t *obj,
    uint16_t value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_TCP_DST_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 6;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_tcp_src_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80001a02); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_tcp_src of_oxm_tcp_src
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_tcp_src_push_wire_values(of_oxm_tcp_src_t *obj)
{

    of_oxm_tcp_src_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_tcp_src object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_tcp_src
 */

of_oxm_tcp_src_t *
of_oxm_tcp_src_new(of_version_t version)
{
    of_oxm_tcp_src_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_TCP_SRC] + of_object_extra_len[version][OF_OXM_TCP_SRC];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_tcp_src_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_tcp_src_init(obj, version, bytes, 0);

    if (of_oxm_tcp_src_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_tcp_src.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_tcp_src_init(of_oxm_tcp_src_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_TCP_SRC] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_TCP_SRC] + of_object_extra_len[version][OF_OXM_TCP_SRC];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_TCP_SRC;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_tcp_src_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_tcp_src.
 * @param obj Pointer to an object of type of_oxm_tcp_src.
 * @param value Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_tcp_src_value_get(
    of_oxm_tcp_src_t *obj,
    uint16_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_TCP_SRC);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_tcp_src.
 * @param obj Pointer to an object of type of_oxm_tcp_src.
 * @param value The value to write into the object
 */
void
of_oxm_tcp_src_value_set(
    of_oxm_tcp_src_t *obj,
    uint16_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_TCP_SRC);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_tcp_src_masked_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80001b04); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_tcp_src_masked of_oxm_tcp_src_masked
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_tcp_src_masked_push_wire_values(of_oxm_tcp_src_masked_t *obj)
{

    of_oxm_tcp_src_masked_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_tcp_src_masked object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_tcp_src_masked
 */

of_oxm_tcp_src_masked_t *
of_oxm_tcp_src_masked_new(of_version_t version)
{
    of_oxm_tcp_src_masked_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_TCP_SRC_MASKED] + of_object_extra_len[version][OF_OXM_TCP_SRC_MASKED];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_tcp_src_masked_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_tcp_src_masked_init(obj, version, bytes, 0);

    if (of_oxm_tcp_src_masked_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_tcp_src_masked.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_tcp_src_masked_init(of_oxm_tcp_src_masked_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_TCP_SRC_MASKED] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_TCP_SRC_MASKED] + of_object_extra_len[version][OF_OXM_TCP_SRC_MASKED];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_TCP_SRC_MASKED;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_tcp_src_masked_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_tcp_src_masked.
 * @param obj Pointer to an object of type of_oxm_tcp_src_masked.
 * @param value Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_tcp_src_masked_value_get(
    of_oxm_tcp_src_masked_t *obj,
    uint16_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_TCP_SRC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_tcp_src_masked.
 * @param obj Pointer to an object of type of_oxm_tcp_src_masked.
 * @param value The value to write into the object
 */
void
of_oxm_tcp_src_masked_value_set(
    of_oxm_tcp_src_masked_t *obj,
    uint16_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_TCP_SRC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Get value_mask from an object of type of_oxm_tcp_src_masked.
 * @param obj Pointer to an object of type of_oxm_tcp_src_masked.
 * @param value_mask Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_tcp_src_masked_value_mask_get(
    of_oxm_tcp_src_masked_t *obj,
    uint16_t *value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_TCP_SRC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 6;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value_mask in an object of type of_oxm_tcp_src_masked.
 * @param obj Pointer to an object of type of_oxm_tcp_src_masked.
 * @param value_mask The value to write into the object
 */
void
of_oxm_tcp_src_masked_value_mask_set(
    of_oxm_tcp_src_masked_t *obj,
    uint16_t value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_TCP_SRC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 6;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_udp_dst_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80002002); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_udp_dst of_oxm_udp_dst
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_udp_dst_push_wire_values(of_oxm_udp_dst_t *obj)
{

    of_oxm_udp_dst_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_udp_dst object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_udp_dst
 */

of_oxm_udp_dst_t *
of_oxm_udp_dst_new(of_version_t version)
{
    of_oxm_udp_dst_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_UDP_DST] + of_object_extra_len[version][OF_OXM_UDP_DST];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_udp_dst_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_udp_dst_init(obj, version, bytes, 0);

    if (of_oxm_udp_dst_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_udp_dst.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_udp_dst_init(of_oxm_udp_dst_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_UDP_DST] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_UDP_DST] + of_object_extra_len[version][OF_OXM_UDP_DST];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_UDP_DST;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_udp_dst_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_udp_dst.
 * @param obj Pointer to an object of type of_oxm_udp_dst.
 * @param value Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_udp_dst_value_get(
    of_oxm_udp_dst_t *obj,
    uint16_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_UDP_DST);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_udp_dst.
 * @param obj Pointer to an object of type of_oxm_udp_dst.
 * @param value The value to write into the object
 */
void
of_oxm_udp_dst_value_set(
    of_oxm_udp_dst_t *obj,
    uint16_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_UDP_DST);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_udp_dst_masked_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80002104); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_udp_dst_masked of_oxm_udp_dst_masked
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_udp_dst_masked_push_wire_values(of_oxm_udp_dst_masked_t *obj)
{

    of_oxm_udp_dst_masked_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_udp_dst_masked object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_udp_dst_masked
 */

of_oxm_udp_dst_masked_t *
of_oxm_udp_dst_masked_new(of_version_t version)
{
    of_oxm_udp_dst_masked_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_UDP_DST_MASKED] + of_object_extra_len[version][OF_OXM_UDP_DST_MASKED];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_udp_dst_masked_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_udp_dst_masked_init(obj, version, bytes, 0);

    if (of_oxm_udp_dst_masked_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_udp_dst_masked.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_udp_dst_masked_init(of_oxm_udp_dst_masked_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_UDP_DST_MASKED] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_UDP_DST_MASKED] + of_object_extra_len[version][OF_OXM_UDP_DST_MASKED];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_UDP_DST_MASKED;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_udp_dst_masked_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_udp_dst_masked.
 * @param obj Pointer to an object of type of_oxm_udp_dst_masked.
 * @param value Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_udp_dst_masked_value_get(
    of_oxm_udp_dst_masked_t *obj,
    uint16_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_UDP_DST_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_udp_dst_masked.
 * @param obj Pointer to an object of type of_oxm_udp_dst_masked.
 * @param value The value to write into the object
 */
void
of_oxm_udp_dst_masked_value_set(
    of_oxm_udp_dst_masked_t *obj,
    uint16_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_UDP_DST_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Get value_mask from an object of type of_oxm_udp_dst_masked.
 * @param obj Pointer to an object of type of_oxm_udp_dst_masked.
 * @param value_mask Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_udp_dst_masked_value_mask_get(
    of_oxm_udp_dst_masked_t *obj,
    uint16_t *value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_UDP_DST_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 6;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value_mask in an object of type of_oxm_udp_dst_masked.
 * @param obj Pointer to an object of type of_oxm_udp_dst_masked.
 * @param value_mask The value to write into the object
 */
void
of_oxm_udp_dst_masked_value_mask_set(
    of_oxm_udp_dst_masked_t *obj,
    uint16_t value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_UDP_DST_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 6;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_udp_src_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80001e02); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_udp_src of_oxm_udp_src
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_udp_src_push_wire_values(of_oxm_udp_src_t *obj)
{

    of_oxm_udp_src_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_udp_src object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_udp_src
 */

of_oxm_udp_src_t *
of_oxm_udp_src_new(of_version_t version)
{
    of_oxm_udp_src_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_UDP_SRC] + of_object_extra_len[version][OF_OXM_UDP_SRC];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_udp_src_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_udp_src_init(obj, version, bytes, 0);

    if (of_oxm_udp_src_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_udp_src.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_udp_src_init(of_oxm_udp_src_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_UDP_SRC] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_UDP_SRC] + of_object_extra_len[version][OF_OXM_UDP_SRC];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_UDP_SRC;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_udp_src_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_udp_src.
 * @param obj Pointer to an object of type of_oxm_udp_src.
 * @param value Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_udp_src_value_get(
    of_oxm_udp_src_t *obj,
    uint16_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_UDP_SRC);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_udp_src.
 * @param obj Pointer to an object of type of_oxm_udp_src.
 * @param value The value to write into the object
 */
void
of_oxm_udp_src_value_set(
    of_oxm_udp_src_t *obj,
    uint16_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_UDP_SRC);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_udp_src_masked_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80001f04); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_udp_src_masked of_oxm_udp_src_masked
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_udp_src_masked_push_wire_values(of_oxm_udp_src_masked_t *obj)
{

    of_oxm_udp_src_masked_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_udp_src_masked object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_udp_src_masked
 */

of_oxm_udp_src_masked_t *
of_oxm_udp_src_masked_new(of_version_t version)
{
    of_oxm_udp_src_masked_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_UDP_SRC_MASKED] + of_object_extra_len[version][OF_OXM_UDP_SRC_MASKED];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_udp_src_masked_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_udp_src_masked_init(obj, version, bytes, 0);

    if (of_oxm_udp_src_masked_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_udp_src_masked.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_udp_src_masked_init(of_oxm_udp_src_masked_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_UDP_SRC_MASKED] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_UDP_SRC_MASKED] + of_object_extra_len[version][OF_OXM_UDP_SRC_MASKED];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_UDP_SRC_MASKED;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_udp_src_masked_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_udp_src_masked.
 * @param obj Pointer to an object of type of_oxm_udp_src_masked.
 * @param value Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_udp_src_masked_value_get(
    of_oxm_udp_src_masked_t *obj,
    uint16_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_UDP_SRC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_udp_src_masked.
 * @param obj Pointer to an object of type of_oxm_udp_src_masked.
 * @param value The value to write into the object
 */
void
of_oxm_udp_src_masked_value_set(
    of_oxm_udp_src_masked_t *obj,
    uint16_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_UDP_SRC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Get value_mask from an object of type of_oxm_udp_src_masked.
 * @param obj Pointer to an object of type of_oxm_udp_src_masked.
 * @param value_mask Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_udp_src_masked_value_mask_get(
    of_oxm_udp_src_masked_t *obj,
    uint16_t *value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_UDP_SRC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 6;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value_mask in an object of type of_oxm_udp_src_masked.
 * @param obj Pointer to an object of type of_oxm_udp_src_masked.
 * @param value_mask The value to write into the object
 */
void
of_oxm_udp_src_masked_value_mask_set(
    of_oxm_udp_src_masked_t *obj,
    uint16_t value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_UDP_SRC_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 6;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_vlan_pcp_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80000e01); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_vlan_pcp of_oxm_vlan_pcp
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_vlan_pcp_push_wire_values(of_oxm_vlan_pcp_t *obj)
{

    of_oxm_vlan_pcp_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_vlan_pcp object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_vlan_pcp
 */

of_oxm_vlan_pcp_t *
of_oxm_vlan_pcp_new(of_version_t version)
{
    of_oxm_vlan_pcp_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_VLAN_PCP] + of_object_extra_len[version][OF_OXM_VLAN_PCP];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_vlan_pcp_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_vlan_pcp_init(obj, version, bytes, 0);

    if (of_oxm_vlan_pcp_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_vlan_pcp.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_vlan_pcp_init(of_oxm_vlan_pcp_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_VLAN_PCP] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_VLAN_PCP] + of_object_extra_len[version][OF_OXM_VLAN_PCP];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_VLAN_PCP;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_vlan_pcp_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_vlan_pcp.
 * @param obj Pointer to an object of type of_oxm_vlan_pcp.
 * @param value Pointer to the child object of type
 * uint8_t to be filled out.
 *
 */
void
of_oxm_vlan_pcp_value_get(
    of_oxm_vlan_pcp_t *obj,
    uint8_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_VLAN_PCP);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u8_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_vlan_pcp.
 * @param obj Pointer to an object of type of_oxm_vlan_pcp.
 * @param value The value to write into the object
 */
void
of_oxm_vlan_pcp_value_set(
    of_oxm_vlan_pcp_t *obj,
    uint8_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_VLAN_PCP);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u8_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_vlan_pcp_masked_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80000f02); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_vlan_pcp_masked of_oxm_vlan_pcp_masked
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_vlan_pcp_masked_push_wire_values(of_oxm_vlan_pcp_masked_t *obj)
{

    of_oxm_vlan_pcp_masked_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_vlan_pcp_masked object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_vlan_pcp_masked
 */

of_oxm_vlan_pcp_masked_t *
of_oxm_vlan_pcp_masked_new(of_version_t version)
{
    of_oxm_vlan_pcp_masked_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_VLAN_PCP_MASKED] + of_object_extra_len[version][OF_OXM_VLAN_PCP_MASKED];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_vlan_pcp_masked_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_vlan_pcp_masked_init(obj, version, bytes, 0);

    if (of_oxm_vlan_pcp_masked_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_vlan_pcp_masked.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_vlan_pcp_masked_init(of_oxm_vlan_pcp_masked_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_VLAN_PCP_MASKED] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_VLAN_PCP_MASKED] + of_object_extra_len[version][OF_OXM_VLAN_PCP_MASKED];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_VLAN_PCP_MASKED;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_vlan_pcp_masked_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_vlan_pcp_masked.
 * @param obj Pointer to an object of type of_oxm_vlan_pcp_masked.
 * @param value Pointer to the child object of type
 * uint8_t to be filled out.
 *
 */
void
of_oxm_vlan_pcp_masked_value_get(
    of_oxm_vlan_pcp_masked_t *obj,
    uint8_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_VLAN_PCP_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u8_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_vlan_pcp_masked.
 * @param obj Pointer to an object of type of_oxm_vlan_pcp_masked.
 * @param value The value to write into the object
 */
void
of_oxm_vlan_pcp_masked_value_set(
    of_oxm_vlan_pcp_masked_t *obj,
    uint8_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_VLAN_PCP_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u8_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Get value_mask from an object of type of_oxm_vlan_pcp_masked.
 * @param obj Pointer to an object of type of_oxm_vlan_pcp_masked.
 * @param value_mask Pointer to the child object of type
 * uint8_t to be filled out.
 *
 */
void
of_oxm_vlan_pcp_masked_value_mask_get(
    of_oxm_vlan_pcp_masked_t *obj,
    uint8_t *value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_VLAN_PCP_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 5;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u8_get(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value_mask in an object of type of_oxm_vlan_pcp_masked.
 * @param obj Pointer to an object of type of_oxm_vlan_pcp_masked.
 * @param value_mask The value to write into the object
 */
void
of_oxm_vlan_pcp_masked_value_mask_set(
    of_oxm_vlan_pcp_masked_t *obj,
    uint8_t value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_VLAN_PCP_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 5;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u8_set(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_vlan_vid_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80000c02); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_vlan_vid of_oxm_vlan_vid
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_vlan_vid_push_wire_values(of_oxm_vlan_vid_t *obj)
{

    of_oxm_vlan_vid_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_vlan_vid object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_vlan_vid
 */

of_oxm_vlan_vid_t *
of_oxm_vlan_vid_new(of_version_t version)
{
    of_oxm_vlan_vid_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_VLAN_VID] + of_object_extra_len[version][OF_OXM_VLAN_VID];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_vlan_vid_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_vlan_vid_init(obj, version, bytes, 0);

    if (of_oxm_vlan_vid_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_vlan_vid.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_vlan_vid_init(of_oxm_vlan_vid_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_VLAN_VID] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_VLAN_VID] + of_object_extra_len[version][OF_OXM_VLAN_VID];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_VLAN_VID;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_vlan_vid_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_vlan_vid.
 * @param obj Pointer to an object of type of_oxm_vlan_vid.
 * @param value Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_vlan_vid_value_get(
    of_oxm_vlan_vid_t *obj,
    uint16_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_VLAN_VID);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_vlan_vid.
 * @param obj Pointer to an object of type of_oxm_vlan_vid.
 * @param value The value to write into the object
 */
void
of_oxm_vlan_vid_value_set(
    of_oxm_vlan_vid_t *obj,
    uint16_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_VLAN_VID);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_oxm_vlan_vid_masked_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint32_t *)(buf + 0) = U32_HTON(0x80000d04); /* type_len */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_oxm_vlan_vid_masked of_oxm_vlan_vid_masked
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_oxm_vlan_vid_masked_push_wire_values(of_oxm_vlan_vid_masked_t *obj)
{

    of_oxm_vlan_vid_masked_push_wire_types(obj);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_oxm_vlan_vid_masked object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_oxm_vlan_vid_masked
 */

of_oxm_vlan_vid_masked_t *
of_oxm_vlan_vid_masked_new(of_version_t version)
{
    of_oxm_vlan_vid_masked_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_OXM_VLAN_VID_MASKED] + of_object_extra_len[version][OF_OXM_VLAN_VID_MASKED];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_oxm_vlan_vid_masked_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_oxm_vlan_vid_masked_init(obj, version, bytes, 0);

    if (of_oxm_vlan_vid_masked_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_oxm_vlan_vid_masked.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_oxm_vlan_vid_masked_init(of_oxm_vlan_vid_masked_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_OXM_VLAN_VID_MASKED] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_OXM_VLAN_VID_MASKED] + of_object_extra_len[version][OF_OXM_VLAN_VID_MASKED];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_OXM_VLAN_VID_MASKED;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_oxm_vlan_vid_masked_push_wire_types;

    obj->wire_length_get = of_oxm_wire_length_get;
    obj->wire_type_get = of_oxm_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get value from an object of type of_oxm_vlan_vid_masked.
 * @param obj Pointer to an object of type of_oxm_vlan_vid_masked.
 * @param value Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_vlan_vid_masked_value_get(
    of_oxm_vlan_vid_masked_t *obj,
    uint16_t *value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_VLAN_VID_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value in an object of type of_oxm_vlan_vid_masked.
 * @param obj Pointer to an object of type of_oxm_vlan_vid_masked.
 * @param value The value to write into the object
 */
void
of_oxm_vlan_vid_masked_value_set(
    of_oxm_vlan_vid_masked_t *obj,
    uint16_t value)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_VLAN_VID_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Get value_mask from an object of type of_oxm_vlan_vid_masked.
 * @param obj Pointer to an object of type of_oxm_vlan_vid_masked.
 * @param value_mask Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_oxm_vlan_vid_masked_value_mask_get(
    of_oxm_vlan_vid_masked_t *obj,
    uint16_t *value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_VLAN_VID_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 6;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set value_mask in an object of type of_oxm_vlan_vid_masked.
 * @param obj Pointer to an object of type of_oxm_vlan_vid_masked.
 * @param value_mask The value to write into the object
 */
void
of_oxm_vlan_vid_masked_value_mask_set(
    of_oxm_vlan_vid_masked_t *obj,
    uint16_t value_mask)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_OXM_VLAN_VID_MASKED);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 6;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, value_mask);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"


void
of_queue_prop_experimenter_wire_object_id_get(of_object_t *obj, of_object_id_t *id)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2: {
        uint32_t value = U32_NTOH(*(uint32_t *)(buf + 8)); /* experimenter */
        switch (value) {
        default:
            *id = OF_QUEUE_PROP_EXPERIMENTER;
            break;
        }
        break;
    }
    case OF_VERSION_1_3: {
        uint32_t value = U32_NTOH(*(uint32_t *)(buf + 8)); /* experimenter */
        switch (value) {
        default:
            *id = OF_QUEUE_PROP_EXPERIMENTER;
            break;
        }
        break;
    }
    default:
        LOCI_ASSERT(0);
    }
}


/**
 * \defgroup of_queue_prop_experimenter of_queue_prop_experimenter
 */

/**
 * Create a new of_queue_prop_experimenter object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_queue_prop_experimenter
 */

of_queue_prop_experimenter_t *
of_queue_prop_experimenter_new(of_version_t version)
{
    of_queue_prop_experimenter_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_QUEUE_PROP_EXPERIMENTER] + of_object_extra_len[version][OF_QUEUE_PROP_EXPERIMENTER];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_queue_prop_experimenter_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_queue_prop_experimenter_init(obj, version, bytes, 0);

    return obj;
}

/**
 * Initialize an object of type of_queue_prop_experimenter.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_queue_prop_experimenter_init(of_queue_prop_experimenter_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_QUEUE_PROP_EXPERIMENTER] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_QUEUE_PROP_EXPERIMENTER] + of_object_extra_len[version][OF_QUEUE_PROP_EXPERIMENTER];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_QUEUE_PROP_EXPERIMENTER;

    /* Set up the object's function pointers */

    obj->wire_length_set = of_tlv16_wire_length_set;

    obj->wire_length_get = of_tlv16_wire_length_get;

    obj->wire_type_get = of_queue_prop_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get experimenter from an object of type of_queue_prop_experimenter.
 * @param obj Pointer to an object of type of_queue_prop_experimenter.
 * @param experimenter Pointer to the child object of type
 * uint32_t to be filled out.
 *
 */
void
of_queue_prop_experimenter_experimenter_get(
    of_queue_prop_experimenter_t *obj,
    uint32_t *experimenter)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_QUEUE_PROP_EXPERIMENTER);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 8;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u32_get(wbuf, abs_offset, experimenter);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set experimenter in an object of type of_queue_prop_experimenter.
 * @param obj Pointer to an object of type of_queue_prop_experimenter.
 * @param experimenter The value to write into the object
 */
void
of_queue_prop_experimenter_experimenter_set(
    of_queue_prop_experimenter_t *obj,
    uint32_t experimenter)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_QUEUE_PROP_EXPERIMENTER);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 8;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u32_set(wbuf, abs_offset, experimenter);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Get data from an object of type of_queue_prop_experimenter.
 * @param obj Pointer to an object of type of_queue_prop_experimenter.
 * @param data Pointer to the child object of type
 * of_octets_t to be filled out.
 *
 */
void
of_queue_prop_experimenter_data_get(
    of_queue_prop_experimenter_t *obj,
    of_octets_t *data)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;
    int cur_len = 0; /* Current length of object data */

    LOCI_ASSERT(obj->object_id == OF_QUEUE_PROP_EXPERIMENTER);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 16;
        cur_len = _END_LEN(obj, offset);
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    LOCI_ASSERT(cur_len >= 0 && cur_len < 64 * 1024);
    LOCI_ASSERT(cur_len + abs_offset <= WBUF_CURRENT_BYTES(wbuf));
    data->bytes = cur_len;
    data->data = OF_WIRE_BUFFER_INDEX(wbuf, abs_offset);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set data in an object of type of_queue_prop_experimenter.
 * @param obj Pointer to an object of type of_queue_prop_experimenter.
 * @param data The value to write into the object
 */
int WARN_UNUSED_RESULT
of_queue_prop_experimenter_data_set(
    of_queue_prop_experimenter_t *obj,
    of_octets_t *data)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;
    int cur_len = 0; /* Current length of object data */
    int new_len, delta; /* For set, need new length and delta */

    LOCI_ASSERT(obj->object_id == OF_QUEUE_PROP_EXPERIMENTER);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 16;
        cur_len = _END_LEN(obj, offset);
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    LOCI_ASSERT(cur_len >= 0 && cur_len < 64 * 1024);
    new_len = data->bytes;
    of_wire_buffer_grow(wbuf, abs_offset + (new_len - cur_len));
    of_wire_buffer_octets_data_set(wbuf, abs_offset, data, cur_len);

    /* Not scalar, update lengths if needed */
    delta = new_len - cur_len;
    if (delta != 0) {
        /* Update parent(s) */
        of_object_parent_length_update((of_object_t *)obj, delta);
    }

    OF_LENGTH_CHECK_ASSERT(obj);

    return OF_ERROR_NONE;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_queue_prop_max_rate_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint16_t *)(buf + 0) = U16_HTON(0x2); /* type */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_queue_prop_max_rate of_queue_prop_max_rate
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_queue_prop_max_rate_push_wire_values(of_queue_prop_max_rate_t *obj)
{

    of_queue_prop_max_rate_push_wire_types(obj);

    /* TLV obj; set length */
    of_tlv16_wire_length_set((of_object_t *)obj, obj->length);

    return OF_ERROR_NONE;
}

/**
 * Create a new of_queue_prop_max_rate object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_queue_prop_max_rate
 */

of_queue_prop_max_rate_t *
of_queue_prop_max_rate_new(of_version_t version)
{
    of_queue_prop_max_rate_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_QUEUE_PROP_MAX_RATE] + of_object_extra_len[version][OF_QUEUE_PROP_MAX_RATE];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_queue_prop_max_rate_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_queue_prop_max_rate_init(obj, version, bytes, 0);

    if (of_queue_prop_max_rate_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_queue_prop_max_rate.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_queue_prop_max_rate_init(of_queue_prop_max_rate_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_QUEUE_PROP_MAX_RATE] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_QUEUE_PROP_MAX_RATE] + of_object_extra_len[version][OF_QUEUE_PROP_MAX_RATE];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_QUEUE_PROP_MAX_RATE;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_queue_prop_max_rate_push_wire_types;

    obj->wire_length_set = of_tlv16_wire_length_set;

    obj->wire_length_get = of_tlv16_wire_length_get;

    obj->wire_type_get = of_queue_prop_wire_object_id_get;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Get rate from an object of type of_queue_prop_max_rate.
 * @param obj Pointer to an object of type of_queue_prop_max_rate.
 * @param rate Pointer to the child object of type
 * uint16_t to be filled out.
 *
 */
void
of_queue_prop_max_rate_rate_get(
    of_queue_prop_max_rate_t *obj,
    uint16_t *rate)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_QUEUE_PROP_MAX_RATE);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 8;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_get(wbuf, abs_offset, rate);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set rate in an object of type of_queue_prop_max_rate.
 * @param obj Pointer to an object of type of_queue_prop_max_rate.
 * @param rate The value to write into the object
 */
void
of_queue_prop_max_rate_rate_set(
    of_queue_prop_max_rate_t *obj,
    uint16_t rate)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_QUEUE_PROP_MAX_RATE);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 8;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u16_set(wbuf, abs_offset, rate);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_role_reply_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint8_t *)(buf + 0) = obj->version; /* version */
        *(uint8_t *)(buf + 1) = 0x19; /* type */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_role_reply of_role_reply
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_role_reply_push_wire_values(of_role_reply_t *obj)
{

    of_role_reply_push_wire_types(obj);

    /* Message obj; set length */
    of_message_t msg;

    if ((msg = OF_OBJECT_TO_MESSAGE(obj)) != NULL) {
        of_message_length_set(msg, obj->length);
    }

    return OF_ERROR_NONE;
}

/**
 * Create a new of_role_reply object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_role_reply
 */

of_role_reply_t *
of_role_reply_new(of_version_t version)
{
    of_role_reply_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_ROLE_REPLY] + of_object_extra_len[version][OF_ROLE_REPLY];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_role_reply_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_role_reply_init(obj, version, bytes, 0);

    if (of_role_reply_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_role_reply.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_role_reply_init(of_role_reply_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_ROLE_REPLY] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_ROLE_REPLY] + of_object_extra_len[version][OF_ROLE_REPLY];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_ROLE_REPLY;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_role_reply_push_wire_types;

    obj->wire_length_get = of_object_message_wire_length_get;
    obj->wire_length_set = of_object_message_wire_length_set;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Create a new of_role_reply object and bind it to an existing message
 *
 * @param msg The message to bind the new object to
 * @return Pointer to the newly create object or NULL on error
 *
 * \ingroup of_role_reply
 */

of_role_reply_t *
of_role_reply_new_from_message(of_message_t msg)
{
    of_role_reply_t *obj = NULL;
    of_version_t version;
    int length;

    if (msg == NULL) return NULL;

    version = of_message_version_get(msg);
    if (!OF_VERSION_OKAY(version)) return NULL;

    length = of_message_length_get(msg);

    if ((obj = (of_role_reply_t *)of_object_new(-1)) == NULL) {
        return NULL;
    }

    of_role_reply_init(obj, version, 0, 0);

    if ((of_object_buffer_bind((of_object_t *)obj, OF_MESSAGE_TO_BUFFER(msg),
                               length, OF_MESSAGE_FREE_FUNCTION)) < 0) {
       FREE(obj);
       return NULL;
    }
    obj->length = length;
    obj->version = version;

    return obj;
}

/**
 * Get xid from an object of type of_role_reply.
 * @param obj Pointer to an object of type of_role_reply.
 * @param xid Pointer to the child object of type
 * uint32_t to be filled out.
 *
 */
void
of_role_reply_xid_get(
    of_role_reply_t *obj,
    uint32_t *xid)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_ROLE_REPLY);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u32_get(wbuf, abs_offset, xid);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set xid in an object of type of_role_reply.
 * @param obj Pointer to an object of type of_role_reply.
 * @param xid The value to write into the object
 */
void
of_role_reply_xid_set(
    of_role_reply_t *obj,
    uint32_t xid)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_ROLE_REPLY);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u32_set(wbuf, abs_offset, xid);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Get role from an object of type of_role_reply.
 * @param obj Pointer to an object of type of_role_reply.
 * @param role Pointer to the child object of type
 * uint32_t to be filled out.
 *
 */
void
of_role_reply_role_get(
    of_role_reply_t *obj,
    uint32_t *role)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_ROLE_REPLY);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 8;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u32_get(wbuf, abs_offset, role);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set role in an object of type of_role_reply.
 * @param obj Pointer to an object of type of_role_reply.
 * @param role The value to write into the object
 */
void
of_role_reply_role_set(
    of_role_reply_t *obj,
    uint32_t role)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_ROLE_REPLY);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 8;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u32_set(wbuf, abs_offset, role);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Get generation_id from an object of type of_role_reply.
 * @param obj Pointer to an object of type of_role_reply.
 * @param generation_id Pointer to the child object of type
 * uint64_t to be filled out.
 *
 */
void
of_role_reply_generation_id_get(
    of_role_reply_t *obj,
    uint64_t *generation_id)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_ROLE_REPLY);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 16;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u64_get(wbuf, abs_offset, generation_id);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set generation_id in an object of type of_role_reply.
 * @param obj Pointer to an object of type of_role_reply.
 * @param generation_id The value to write into the object
 */
void
of_role_reply_generation_id_set(
    of_role_reply_t *obj,
    uint64_t generation_id)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_ROLE_REPLY);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 16;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u64_set(wbuf, abs_offset, generation_id);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}
/* Copyright (c) 2008 The Board of Trustees of The Leland Stanford Junior University */
/* Copyright (c) 2011, 2012 Open Networking Foundation */
/* Copyright (c) 2012, 2013 Big Switch Networks, Inc. */
/* See the file LICENSE.loci which should have been included in the source distribution */
#ifdef __GNUC__

#ifdef __linux__
/* glibc */
#include <features.h>
#else
/* NetBSD etc */
#include <sys/cdefs.h>
#ifdef __GNUC_PREREQ__
#define __GNUC_PREREQ __GNUC_PREREQ__
#endif
#endif

#ifndef __GNUC_PREREQ
/* fallback */
#define __GNUC_PREREQ(maj, min) 0
#endif

#if __GNUC_PREREQ(4,6)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#endif

#include "loci_log.h"
#include "loci_int.h"

static void
of_role_request_push_wire_types(of_object_t *obj)
{
    unsigned char *buf = OF_OBJECT_BUFFER_INDEX(obj, 0);
    switch (obj->version) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        *(uint8_t *)(buf + 0) = obj->version; /* version */
        *(uint8_t *)(buf + 1) = 0x18; /* type */
        break;
    default:
        UNREACHABLE();
    }
}



/**
 * \defgroup of_role_request of_role_request
 */

/**
 * Helper function to push values into the wire buffer
 */
static inline int
of_role_request_push_wire_values(of_role_request_t *obj)
{

    of_role_request_push_wire_types(obj);

    /* Message obj; set length */
    of_message_t msg;

    if ((msg = OF_OBJECT_TO_MESSAGE(obj)) != NULL) {
        of_message_length_set(msg, obj->length);
    }

    return OF_ERROR_NONE;
}

/**
 * Create a new of_role_request object
 *
 * @param version The wire version to use for the object
 * @return Pointer to the newly create object or NULL on error
 *
 * Initializes the new object with it's default fixed length associating
 * a new underlying wire buffer.
 *
 * Use new_from_message to bind an existing message to a message object,
 * or a _get function for non-message objects.
 *
 * \ingroup of_role_request
 */

of_role_request_t *
of_role_request_new(of_version_t version)
{
    of_role_request_t *obj;
    int bytes;

    bytes = of_object_fixed_len[version][OF_ROLE_REQUEST] + of_object_extra_len[version][OF_ROLE_REQUEST];

    /* Allocate a maximum-length wire buffer assuming we'll be appending to it. */
    if ((obj = (of_role_request_t *)of_object_new(OF_WIRE_BUFFER_MAX_LENGTH)) == NULL) {
        return NULL;
    }

    of_role_request_init(obj, version, bytes, 0);

    if (of_role_request_push_wire_values(obj) < 0) {
        FREE(obj);
        return NULL;
    }

    return obj;
}

/**
 * Initialize an object of type of_role_request.
 *
 * @param obj Pointer to the object to initialize
 * @param version The wire version to use for the object
 * @param bytes How many bytes in the object
 * @param clean_wire Boolean: If true, clear the wire object control struct
 *
 * If bytes < 0, then the default fixed length is used for the object
 *
 * This is a "coerce" function that sets up the pointers for the
 * accessors properly.
 *
 * If anything other than 0 is passed in for the buffer size, the underlying
 * wire buffer will have 'grow' called.
 */

void
of_role_request_init(of_role_request_t *obj,
    of_version_t version, int bytes, int clean_wire)
{

    LOCI_ASSERT(of_object_fixed_len[version][OF_ROLE_REQUEST] >= 0);
    if (clean_wire) {
        MEMSET(obj, 0, sizeof(*obj));
    }
    if (bytes < 0) {
        bytes = of_object_fixed_len[version][OF_ROLE_REQUEST] + of_object_extra_len[version][OF_ROLE_REQUEST];
    }
    obj->version = version;
    obj->length = bytes;
    obj->object_id = OF_ROLE_REQUEST;

    /* Set up the object's function pointers */

    obj->wire_type_set = of_role_request_push_wire_types;

    obj->wire_length_get = of_object_message_wire_length_get;
    obj->wire_length_set = of_object_message_wire_length_set;

    /* Grow the wire buffer */
    if (obj->wire_object.wbuf != NULL) {
        int tot_bytes;

        tot_bytes = bytes + obj->wire_object.obj_offset;
        of_wire_buffer_grow(obj->wire_object.wbuf, tot_bytes);
    }
}


/**
 * Create a new of_role_request object and bind it to an existing message
 *
 * @param msg The message to bind the new object to
 * @return Pointer to the newly create object or NULL on error
 *
 * \ingroup of_role_request
 */

of_role_request_t *
of_role_request_new_from_message(of_message_t msg)
{
    of_role_request_t *obj = NULL;
    of_version_t version;
    int length;

    if (msg == NULL) return NULL;

    version = of_message_version_get(msg);
    if (!OF_VERSION_OKAY(version)) return NULL;

    length = of_message_length_get(msg);

    if ((obj = (of_role_request_t *)of_object_new(-1)) == NULL) {
        return NULL;
    }

    of_role_request_init(obj, version, 0, 0);

    if ((of_object_buffer_bind((of_object_t *)obj, OF_MESSAGE_TO_BUFFER(msg),
                               length, OF_MESSAGE_FREE_FUNCTION)) < 0) {
       FREE(obj);
       return NULL;
    }
    obj->length = length;
    obj->version = version;

    return obj;
}

/**
 * Get xid from an object of type of_role_request.
 * @param obj Pointer to an object of type of_role_request.
 * @param xid Pointer to the child object of type
 * uint32_t to be filled out.
 *
 */
void
of_role_request_xid_get(
    of_role_request_t *obj,
    uint32_t *xid)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_ROLE_REQUEST);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u32_get(wbuf, abs_offset, xid);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set xid in an object of type of_role_request.
 * @param obj Pointer to an object of type of_role_request.
 * @param xid The value to write into the object
 */
void
of_role_request_xid_set(
    of_role_request_t *obj,
    uint32_t xid)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_ROLE_REQUEST);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 4;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u32_set(wbuf, abs_offset, xid);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Get role from an object of type of_role_request.
 * @param obj Pointer to an object of type of_role_request.
 * @param role Pointer to the child object of type
 * uint32_t to be filled out.
 *
 */
void
of_role_request_role_get(
    of_role_request_t *obj,
    uint32_t *role)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_ROLE_REQUEST);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 8;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u32_get(wbuf, abs_offset, role);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set role in an object of type of_role_request.
 * @param obj Pointer to an object of type of_role_request.
 * @param role The value to write into the object
 */
void
of_role_request_role_set(
    of_role_request_t *obj,
    uint32_t role)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_ROLE_REQUEST);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 8;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u32_set(wbuf, abs_offset, role);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Get generation_id from an object of type of_role_request.
 * @param obj Pointer to an object of type of_role_request.
 * @param generation_id Pointer to the child object of type
 * uint64_t to be filled out.
 *
 */
void
of_role_request_generation_id_get(
    of_role_request_t *obj,
    uint64_t *generation_id)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_ROLE_REQUEST);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 16;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u64_get(wbuf, abs_offset, generation_id);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}

/**
 * Set generation_id in an object of type of_role_request.
 * @param obj Pointer to an object of type of_role_request.
 * @param generation_id The value to write into the object
 */
void
of_role_request_generation_id_set(
    of_role_request_t *obj,
    uint64_t generation_id)
{
    of_wire_buffer_t *wbuf;
    int offset = 0; /* Offset of value relative to the start obj */
    int abs_offset; /* Offset of value relative to start of wbuf */
    of_version_t ver;

    LOCI_ASSERT(obj->object_id == OF_ROLE_REQUEST);
    ver = obj->version;
    wbuf = OF_OBJECT_TO_WBUF(obj);
    LOCI_ASSERT(wbuf != NULL);

    /* By version, determine offset and current length (where needed) */
    switch (ver) {
    case OF_VERSION_1_2:
    case OF_VERSION_1_3:
        offset = 16;
        break;
    default:
        LOCI_ASSERT(0);
    }

    abs_offset = OF_OBJECT_ABSOLUTE_OFFSET(obj, offset);
    LOCI_ASSERT(abs_offset >= 0);
    of_wire_buffer_u64_set(wbuf, abs_offset, generation_id);

    OF_LENGTH_CHECK_ASSERT(obj);

    return ;
}