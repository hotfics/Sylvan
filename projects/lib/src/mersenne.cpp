/*
    This file is part of Sylvan.
    Copyright (C) 2008-2018 Cute Chess authors
    Copyright (C) 2019 Wilbert Lee

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Sylvan.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mersenne.h"
#include <QMutex>

namespace {

int s_index = 0;
quint32 s_mt[624];

void generateNumbers()
{
    for (int i = 0; i < 624; i++)
    {
        quint32 y = (s_mt[i] & 0x1) + (s_mt[(i + 1) % 624] & 0x7fffffff);
        s_mt[i] = s_mt[(i + 397) % 624] ^ (y >> 1);

        if (y % 2)
            s_mt[i] ^= 0x9908b0df;
    }
}

} // anonymous namespace

void Mersenne::initialize(quint32 seed)
{
    s_mt[0] = seed;

    for (int i = 1; i < 624; i++)
        s_mt[i] = (0x6c078965 * (s_mt[i - 1] ^ (s_mt[i - 1] >> 30)) + i) & 0xffffffff;
}

quint32 Mersenne::random()
{
    static QMutex mutex;
    mutex.lock();

    if (s_index == 0)
        generateNumbers();

    quint32 y = s_mt[s_index];
    y ^= y >> 11;
    y ^= (y << 7) & 0x9d2c5680;
    y ^= (y << 15) & 0xefc60000;
    y ^= y >> 18;

    s_index = (s_index + 1) % 624;
    mutex.unlock();

    return y;
}
