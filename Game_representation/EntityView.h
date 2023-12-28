#ifndef PACMANV0_ENTITYVIEW_H
#define PACMANV0_ENTITYVIEW_H
#include "../Game_logic/Observer.h"
#include "../Game_logic/Entities/Subject.h"
#include "../Game_logic/Entities/EntityModel.h"

class EntityView : public Observer, public std::enable_shared_from_this<EntityView>{
public:
    EntityView(EntityModel& entityModel);

    void Update(const std::string& message_from_subject) override;

    void RemoveFromTheList();


private:
    std::string _message_from_subject;
    EntityModel& _entityModel;

};



#endif //PACMANV0_ENTITYVIEW_H
