#include "TextureExporter.h"
#include "../ZAPD/ZFile.h"

void ExporterExample_Texture::Save(ZResource* res, fs::path outPath, BinaryWriter* writer)
{
	ZTexture* tex = (ZTexture*)res;

	auto data = tex->parent->GetRawData();

	for (int i = tex->GetRawDataIndex(); i < tex->GetRawDataIndex() + tex->GetRawDataSize(); i++)
		writer->Write(data[i]);
}