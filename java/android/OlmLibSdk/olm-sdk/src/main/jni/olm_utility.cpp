/*
 * Copyright 2016 OpenMarket Ltd
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

#include "olm_jni.h"
#include "olm_utility.h"

/**
 * Verify an ed25519 signature.
 * If the key was too small then the message will be "OLM.INVALID_BASE64".
 * If the signature was invalid then the message will be "OLM.BAD_MESSAGE_MAC".
 * @param aKey the ed25519 key.
 * @param aMessage the message which was signed.
 * @param aSignature the base64-encoded signature to be checked.
 * @param the result error if there is a problem with the verification.
 * @return true if validation succeed, false otherwise
 */
JNIEXPORT bool OLM_UTILITY_FUNC_DEF(ed25519VerifyJni)(JNIEnv *env, jobject thiz, jstring aKey, jstring aMessage, jstring aSignature, jobject aErrorMessage)
{
    bool retCode = false;



    return retCode;
}