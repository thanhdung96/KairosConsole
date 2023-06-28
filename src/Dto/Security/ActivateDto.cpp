#include "Dto/Security/ActivateDto.h"

namespace DTO::Security {
    ActivateDto::ActivateDto(string Username, string Hashcode): BaseSecurityDto(Username)
    {
        m_Hashcode = Hashcode;
    }
}
