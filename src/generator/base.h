#pragma once

#include "adt/instance.h"

template<class TItem>
class Generator {
public:
    virtual Instance<TItem> Generate() const = 0;
};
