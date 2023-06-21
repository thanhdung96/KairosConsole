#ifndef KAIROSCONSOLE_BASEDTO_H
#define KAIROSCONSOLE_BASEDTO_H

#include <string>
#include "Network/Helper/json.hpp"

namespace DTO {
    using json = nlohmann::json;
    using namespace std;

    class BaseDto {
        public:
            virtual void FromJson(const json& jsonObject);
            virtual json ToJson(bool toSubmit);

        protected:
            BaseDto() = default;
            ~BaseDto() = default;
    };
}
#endif //KAIROSCONSOLE_BASEDTO_H
