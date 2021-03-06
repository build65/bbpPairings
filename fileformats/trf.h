/*
 * This file is part of BBP Pairings, a Swiss-system chess tournament engine
 * Copyright (C) 2016  Jeremy Bierema
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 3.0, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef TRF_H
#define TRF_H

#include <deque>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include <tournament/tournament.h>
#include <utility/uintstringconversion.h>

namespace fileformats
{
  namespace trf
  {
    /**
     * A type for storing the contents of a TRF file, so that the new tournament
     * can be swapped into it.
     */
    struct FileData
    {
      /**
       * The lines of the original file, in file order, though parts that are
       * not applicable to the output may be removed.
       */
      std::deque<std::u32string> lines;
      /**
       * Indices into the lines deque indicating which of the lines correspond
       * to which player IDs.
       */
      std::vector<decltype(lines)::size_type> playerLines;
    };

    tournament::Tournament
      readFile(std::istream &, bool, FileData *fileData = nullptr);

    /**
     * Write the tournament name to the output stream, including the provided
     * seed.
     */
    template <typename Seed>
    void writeSeed(std::ostream &outputStream, Seed seed)
    {
      outputStream << "012 AutoTest Tournament "
        << utility::uintstringconversion::toString(seed)
        << '\r';
      outputStream.flush();
    }

    void writeFile(std::ostream &, const tournament::Tournament &);
    void writeFile(
      std::ostream &,
      const tournament::Tournament &,
      FileData &&);
  }
}

#endif
