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

#ifndef TRINITYSERVER_PACKET_BUILDER_H
#define TRINITYSERVER_PACKET_BUILDER_H

#include "Define.h"

class ByteBuffer;

namespace G3D
{
    class Vector3;
}

namespace Movement
{
    using G3D::Vector3;

    class MoveSpline;

    class WH_GAME_API PacketBuilder
    {
        static void WriteCommonMonsterMovePart(const MoveSpline& mov, ByteBuffer& data);
    public:
        static void WriteMonsterMove(const MoveSpline& mov, ByteBuffer& data);
        static void WriteStopMovement(Vector3 const& loc, uint32 splineId, ByteBuffer& data);
        static void WriteCreate(const MoveSpline& mov, ByteBuffer& data);
    };
}
#endif // TRINITYSERVER_PACKET_BUILDER_H
