/*
 * This file is part of the WarheadCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __WARHEAD_SECRETMGR_H__
#define __WARHEAD_SECRETMGR_H__

#include "BigNumber.h"
#include "LogCommon.h"
#include "Optional.h"
#include <array>
#include <mutex>

enum Secrets : uint32
{
    SECRET_TOTP_MASTER_KEY = 0,

    // only add new indices right above this line
    NUM_SECRETS
};

class WH_SHARED_API SecretMgr
{
public:
    struct Secret
    {
        public:
            explicit operator bool() const { return (state == PRESENT); }
            BigNumber const& operator*() const { return value; }
            BigNumber const* operator->() const { return &value; }
            [[nodiscard]] bool IsAvailable() const { return (state != NOT_LOADED_YET) && (state != LOAD_FAILED); }

        private:
            std::mutex lock;
            enum { NOT_LOADED_YET, LOAD_FAILED, NOT_PRESENT, PRESENT } state = NOT_LOADED_YET;
            BigNumber value;

        friend class SecretMgr;
    };

    static SecretMgr* instance();

    void Initialize();
    Secret const& GetSecret(Secrets i);

private:
    void AttemptLoad(Secrets i, Warhead::LogLevel errorLevel, std::unique_lock<std::mutex> const&);
    [[nodiscard]] Optional<std::string> AttemptTransition(Secrets i, Optional<BigNumber> const& newSecret, Optional<BigNumber> const& oldSecret, bool hadOldSecret) const;

    std::array<Secret, NUM_SECRETS> _secrets;

    SecretMgr() = default;
    ~SecretMgr() = default;
    SecretMgr(SecretMgr const&) = delete;
    SecretMgr(SecretMgr&&) = delete;
    SecretMgr& operator=(SecretMgr const&) = delete;
    SecretMgr& operator=(SecretMgr&&) = delete;
};

#define sSecretMgr SecretMgr::instance()

#endif
