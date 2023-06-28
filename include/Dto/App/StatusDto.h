#ifndef STATUSDTO_H
#define STATUSDTO_H

#include "Dto/BaseDto.h"
#include "Network/Helper/json.hpp"

namespace DTO::App {
using json = nlohmann::json;

    class StatusDto : public BaseDto
    {
        public:
            StatusDto() = default;
            ~StatusDto() = default;

            bool Active() const;
            void setActive(bool newActive);

            void FromJson(const json& jsonObject) override;
            json ToJson(bool toSubmit) override;

        private:
            bool m_Active;
    };
}

#endif // STATUSDTO_H
