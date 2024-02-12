#include <NonCloningDynamicComponent.hpp>

NonCloningDynamicComponent::NonCloningDynamicComponent(const std::vector<Direction>& directions, const NonCloningDynamicComponent::WorkFunctionType& workFunction):
    Component(directions), m_workFunc(workFunction)
{}

bool NonCloningDynamicComponent::work(Current::Ptr current, std::vector<Current::Ptr>& currentVector)
{
    if(!Component::work(current, currentVector))
    {
        return false;
    }

    std::vector<Current::Ptr> newCurrents;
    bool result = m_workFunc(current, newCurrents);
    currentVector.insert(currentVector.end(), std::make_move_iterator(newCurrents.begin()), std::make_move_iterator(newCurrents.end()));

    return result;
}