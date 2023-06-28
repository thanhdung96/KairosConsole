#include "Dto/BaseDto.h"

namespace DTO {
    void BaseDto::FromJson(const json& jsonObject) { }

    json BaseDto::ToJson(bool toSubmit) {
        json j;
        return j;
    }
}

