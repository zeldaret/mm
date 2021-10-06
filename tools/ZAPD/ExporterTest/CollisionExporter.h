#pragma once

#include "ZResource.h"
#include "ZCollision.h"

class ExporterExample_Collision : public ZResourceExporter
{
public:
	void Save(ZResource* res, fs::path outPath, BinaryWriter* writer) override;
};