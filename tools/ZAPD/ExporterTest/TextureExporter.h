#pragma once

#include "ZResource.h"
#include "ZTexture.h"
#include <Utils/BinaryWriter.h>

class ExporterExample_Texture : public ZResourceExporter
{
public:
	virtual void Save(ZResource* res, fs::path outPath, BinaryWriter* writer) override;
};