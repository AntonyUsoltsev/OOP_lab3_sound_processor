//
// Created by Antony on 27.11.2022.
//

#ifndef LAB3_SOUND_PROCESSOR_FACTORY_H
#define LAB3_SOUND_PROCESSOR_FACTORY_H

#include <map>

template <class ID, class Base> class Converters_Factory {
private:
    typedef Base *(*fInstantiator)();

    std::map<ID, fInstantiator> classes;

    template <class Derived> static Base *instantiator() {
        return new Derived();
    }

public:
    Converters_Factory() = default;

    template <class Derived> void add(ID id) {
        classes[id] = &instantiator<Derived>;
    }

    fInstantiator get(ID id) {
        return classes[id];
    }
};

#endif //LAB3_SOUND_PROCESSOR_FACTORY_H
