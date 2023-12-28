
#include "EntityView.h"



EntityView::EntityView(EntityModel &entityModel) : _entityModel{entityModel}{

    std::shared_ptr<EntityView> sharedThis = shared_from_this();

    this -> _entityModel.Attach(sharedThis);

}

void EntityView::Update(const std::string &message_from_subject) {
    _message_from_subject = message_from_subject;
}

void EntityView::RemoveFromTheList() {

    std::shared_ptr<EntityView> sharedThis = shared_from_this();
    _entityModel.Detach(sharedThis);

}
