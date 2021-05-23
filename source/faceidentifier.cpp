#include "faceidentifier.h"
#include "face.h"

FaceIdentifier::FaceIdentifier(std::shared_ptr<JsonDB> db, double diff)
    :db(db), diff(diff)
{

}

void FaceIdentifier::identify(FacePoints pointSet)
{
    std::vector<Face> faces = db->get();
    for(auto& face : faces){
        auto compare = face.compare(pointSet);
        if(!compare.first.isEmpty()){
            if(compare.second < diff){
                emit identified(compare.first);
                return;
            }
        }
    }
    emit identified(QString());
}
