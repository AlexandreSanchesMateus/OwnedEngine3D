#include "OwnedEngine3D/Component/EntityInfo.h"

EntityInfo::EntityInfo() : m_name("nameless"), m_layer(0), m_tag(0)
{

}

EntityInfo::EntityInfo(const std::string& name, std::uint16_t tag, std::uint16_t layer) : m_name(name), m_tag(tag), m_layer(layer)
{

}