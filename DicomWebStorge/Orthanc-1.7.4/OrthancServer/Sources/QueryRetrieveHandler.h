/**
 * Orthanc - A Lightweight, RESTful DICOM Store
 * Copyright (C) 2012-2016 Sebastien Jodogne, Medical Physics
 * Department, University Hospital of Liege, Belgium
 * Copyright (C) 2017-2020 Osimis S.A., Belgium
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * In addition, as a special exception, the copyright holders of this
 * program give permission to link the code of its release with the
 * OpenSSL project's "OpenSSL" library (or with modified versions of it
 * that use the same license as the "OpenSSL" library), and distribute
 * the linked executables. You must obey the GNU General Public License
 * in all respects for all of the code used other than "OpenSSL". If you
 * modify file(s) with this exception, you may extend this exception to
 * your version of the file(s), but you are not obligated to do so. If
 * you do not wish to do so, delete this exception statement from your
 * version. If you delete this exception statement from all source files
 * in the program, then also delete it here.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 **/


#pragma once

#include "../../OrthancFramework/Sources/DicomNetworking/DicomFindAnswers.h"
#include "../../OrthancFramework/Sources/DicomNetworking/RemoteModalityParameters.h"

namespace Orthanc
{
  class ServerContext;
  
  class QueryRetrieveHandler : public IDynamicObject
  {
  private:
    ServerContext&             context_;
    std::string                localAet_;
    bool                       done_;
    RemoteModalityParameters   modality_;
    ResourceType               level_;
    DicomMap                   query_;
    DicomFindAnswers           answers_;
    std::string                modalityName_;
    bool                       findNormalized_;

    void Invalidate();

  public:
    explicit QueryRetrieveHandler(ServerContext& context);

    void SetModality(const std::string& symbolicName);

    const RemoteModalityParameters& GetRemoteModality() const
    {
      return modality_;
    }

    const std::string& GetLocalAet() const
    {
      return localAet_;
    }

    const std::string& GetModalitySymbolicName() const
    {
      return modalityName_;
    }

    void SetLevel(ResourceType level);

    ResourceType GetLevel() const
    {
      return level_;
    }

    void SetQuery(const DicomTag& tag,
                  const std::string& value);

    const DicomMap& GetQuery() const
    {
      return query_;
    }

    void CopyStringTag(const DicomMap& from,
                       const DicomTag& tag);

    void Run();

    size_t GetAnswersCount();

    void GetAnswer(DicomMap& target,
                   size_t i);

    bool IsFindNormalized() const
    {
      return findNormalized_;
    }

    void SetFindNormalized(bool normalized);
  };
}
