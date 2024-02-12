#include <CloningDynamicComponent.hpp>
#include <Logger.hpp>

CloningDynamicComponent::CloningDynamicComponent(const std::vector<Direction>& directions, const CloningDynamicComponent::WorkFunctionType& workFunction):
    Cable(directions), m_workFunc(workFunction)
{}

bool CloningDynamicComponent::work(Current::Ptr current, std::vector<Current::Ptr>& currentVector)
{
    if(!Component::work(current, currentVector))
    {
        return false;
    }

    std::vector<Current::Ptr> newCurrents;
    bool result = m_workFunc(current, newCurrents);
    currentVector.insert(currentVector.end(), std::make_move_iterator(newCurrents.begin()), std::make_move_iterator(newCurrents.end()));

    return result && Cable::work(current, currentVector);
}