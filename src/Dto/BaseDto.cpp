#include "Dto/BaseDto.h"
using namespace DTO;

void BaseDto::FromJson(const json& jsonObject) { }

json BaseDto::ToJson() {
    json j;
    return j;
}
