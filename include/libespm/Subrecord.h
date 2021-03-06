/*
 * This file is part of libespm
 *
 * Copyright (C) 2015 Oliver Hamlet
 *
 * libespm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libespm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libespm. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBESPM_SUBRECORD
#define LIBESPM_SUBRECORD

#include <string>
#include <istream>
#include <cstdint>

#include "GameId.h"

namespace libespm {
  class Subrecord {
  private:
    std::string type;
    std::shared_ptr<char> rawData;
    uint32_t rawDataLength;

    static const int typeLength = 4;
    static const int normalFieldSizeLength = 2;
  public:
    inline Subrecord() : rawDataLength(0) {
      type.resize(typeLength);
    }

    inline void read(std::istream& input, GameId gameId, uint32_t dataLengthOverride = 0) {
      input.read(reinterpret_cast<char*>(&type[0]), typeLength);

      if (gameId == GameId::MORROWIND) {
        input.read(reinterpret_cast<char*>(&rawDataLength), sizeof(rawDataLength));
      } else if (dataLengthOverride != 0) {
        input.ignore(normalFieldSizeLength);
        rawDataLength = dataLengthOverride;
      } else {
        input.read(reinterpret_cast<char*>(&rawDataLength), normalFieldSizeLength);
      }

      rawData = std::shared_ptr<char>(new char[rawDataLength], std::default_delete<char[]>());
      input.read(rawData.get(), rawDataLength);
    }

    inline std::string getType() const {
      return type;
    }

    inline std::pair<std::shared_ptr<char>, uint32_t> getRawData() const {
      return std::make_pair(rawData, rawDataLength);
    }
  };
}

#endif
