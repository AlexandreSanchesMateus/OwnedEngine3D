#include "OwnedEngine3D/Component/MetadataComponent.h"

MetadataComponant::MetadataComponant(const std::string& name, std::uint16_t tag, std::uint16_t layer) : metadata(name, tag, layer)
{
}
