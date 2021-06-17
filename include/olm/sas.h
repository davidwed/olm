/* Copyright 2018-2019 New Vector Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef OLM_SAS_H_
#define OLM_SAS_H_

#include <stddef.h>

#include "olm/error.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup SAS Short Authentication String verification
 * These functions are used for verifying keys using the Short Authentication
 * String (SAS) method.
 * @{
 */

typedef struct OlmSAS OlmSAS;

/** A null terminated string describing the most recent error to happen to an
 * SAS object. */
const char * olm_sas_last_error(
    const OlmSAS * sas
);

/** An error code describing the most recent error to happen to an SAS
 * object. */
enum OlmErrorCode olm_sas_last_error_code(
    const OlmSAS * sas
);

/** The size of an SAS object in bytes. */
size_t olm_sas_size(void);

/** Initialize an SAS object using the supplied memory.
 * The supplied memory must be at least `olm_sas_size()` bytes. */
OlmSAS * olm_sas(
    void * memory
);

/** Clears the memory used to back an SAS object. */
size_t olm_clear_sas(
    OlmSAS * sas
);

/** The number of random bytes needed to create an SAS object. */
size_t olm_create_sas_random_length(
    OlmSAS * sas
);

/** Creates a new SAS object.
 *
 * @param[in] sas the SAS object to create, initialized by `olm_sas()`.
 * @param[in] random array of random bytes.  The contents of the buffer may be
 *     overwritten.
 * @param[in] random_length the number of random bytes provided.  Must be at
 *    least `olm_create_sas_random_length()`.
 *
 * @return `olm_error()` on failure.  If there weren't enough random bytes then
 * `olm_sas_last_error()` will be `NOT_ENOUGH_RANDOM`.
 */
size_t olm_create_sas(
    OlmSAS * sas,
    void * random, size_t random_length
);

/** The size of a public key in bytes. */
size_t olm_sas_pubkey_length(OlmSAS * sas);

/** Get the public key for the SAS object.
 *
 * @param[in] sas the SAS object.
 * @param[out] pubkey buffer to store the public key.
 * @param[in] pubkey_length the size of the `pubkey` buffer.  Must be at least
 *   `olm_sas_pubkey_length()`.
 *
 * @return `olm_error()` on failure.  If the `pubkey` buffer is too small, then
 * `olm_sas_last_error()` will be `OUTPUT_BUFFER_TOO_SMALL`.
 */
size_t olm_sas_get_pubkey(
    OlmSAS * sas,
    void * pubkey, size_t pubkey_length
);

/** Sets the public key of other user.
 *
 * @param[in] sas the SAS object.
 * @param[in] their_key the other user's public key.  The contents of the
 *     buffer will be overwritten.
 * @param[in] their_key_length the size of the `their_key` buffer.
 *
 * @return `olm_error()` on failure.  If the `their_key` buffer is too small,
 * then `olm_sas_last_error()` will be `INPUT_BUFFER_TOO_SMALL`.
 */
size_t olm_sas_set_their_key(
    OlmSAS *sas,
    void * their_key, size_t their_key_length
);

/** Checks if their key was set.
 *
 * @param[in] sas the SAS object.
 *
 */
int olm_sas_is_their_key_set(
    OlmSAS *sas
);

/** Generate bytes to use for the short authentication string.
 *
 * @param[in] sas the SAS object.
 * @param[in] info extra information to mix in when generating the bytes, as
 *     per the Matrix spec.
 * @param[in] info_length the length of the `info` parameter.
 * @param[out] output the output buffer.
 * @param[in] output_length the size of the output buffer.  For hex-based SAS
 *     as in the Matrix spec, this will be 5.
 *
 * @return `olm_error()` on failure. If their key wasn't set then
 * `olm_sas_last_error()` will be `SAS_THEIR_KEY_NOT_SET`.
 */
size_t olm_sas_generate_bytes(
    OlmSAS * sas,
    const void * info, size_t info_length,
    void * output, size_t output_length
);

/** The size of the message authentication code generated by
 * olm_sas_calculate_mac()`. */
size_t olm_sas_mac_length(
    OlmSAS *sas
);

/** Generate a message authentication code (MAC) based on the shared secret.
 *
 * @param[in] sas the SAS object.
 * @param[in] input the message to produce the authentication code for.
 * @param[in] input_length the length of the message.
 * @param[in] info extra information to mix in when generating the MAC, as per
 *     the Matrix spec.
 * @param[in] info_length the length of the `info` parameter.
 * @param[out] mac the buffer in which to store the MAC.
 * @param[in] mac_length the size of the `mac` buffer.  Must be at least
 * `olm_sas_mac_length()`
 *
 * @return `olm_error()` on failure.  If the `mac` buffer is too small, then
 * `olm_sas_last_error()` will be `OUTPUT_BUFFER_TOO_SMALL`.
 */
size_t olm_sas_calculate_mac(
    OlmSAS * sas,
    const void * input, size_t input_length,
    const void * info, size_t info_length,
    void * mac, size_t mac_length
);

// A version of the calculate mac function that produces base64 strings that are
// compatible with other base64 implementations.
size_t olm_sas_calculate_mac_fixed_base64(
    OlmSAS * sas,
    const void * input, size_t input_length,
    const void * info, size_t info_length,
    void * mac, size_t mac_length
);

// for compatibility with an old version of Riot
size_t olm_sas_calculate_mac_long_kdf(
    OlmSAS * sas,
    const void * input, size_t input_length,
    const void * info, size_t info_length,
    void * mac, size_t mac_length
);

/** @} */ // end of SAS group

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OLM_SAS_H_ */
