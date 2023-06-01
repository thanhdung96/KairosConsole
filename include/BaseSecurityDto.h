#ifndef BASESECURITYDTO_H
#define BASESECURITYDTO_H

#include <string>

namespace DTO
{
    namespace Security
    {
        using namespace std;
        class BaseSecurityDto
        {
            public:
                BaseSecurityDto();
                virtual ~BaseSecurityDto();

                string GetUsername() { return m_Username; }
                void SetUsername(string val) { m_Username = val; }

            protected:

            private:
                string m_Username;
        };
    }
}
#endif // BASESECURITYDTO_H
