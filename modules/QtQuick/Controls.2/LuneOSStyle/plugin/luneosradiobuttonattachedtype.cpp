#include "luneosradiobuttonattachedtype.h"

LuneOSRadioButtonAttachedType::LuneOSRadioButtonAttachedType(QObject *parent) : QObject(parent)
{

}

bool LuneOSRadioButtonAttachedType::useCollapsedLayout() const
{
    return mUseCollapsedLayout;
}

void LuneOSRadioButtonAttachedType::setUseCollapsedLayout(bool collapsedLayout)
{
    if(mUseCollapsedLayout != collapsedLayout) {
        mUseCollapsedLayout = collapsedLayout;
        useCollapsedLayoutChanged();
    }
}

