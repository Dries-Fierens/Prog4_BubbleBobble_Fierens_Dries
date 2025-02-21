#pragma once
#include <memory>
#include <vector>
#include <typeindex>
#include <type_traits>
#include <algorithm>
#include <string>
#include "Transform.h"
#include "BaseComponent.h"
#include "TextComponent.h"

namespace dae
{
    class Texture2D;

    class GameObject final
    {
    public:
        virtual void Update(float delta_time);
        virtual void Render() const;

        void SetTexture(const std::string& filename);
        void SetPosition(float x, float y);

        GameObject() = default;
        virtual ~GameObject();
        GameObject(const GameObject& other) = delete;
        GameObject(GameObject&& other) = delete;
        GameObject& operator=(const GameObject& other) = delete;
        GameObject& operator=(GameObject&& other) = delete;

        template <typename ComponentType, typename... Args>
        std::shared_ptr<ComponentType> AddComponent(std::shared_ptr<ComponentType> component)
        {
            static_assert(std::is_base_of<BaseComponent, ComponentType>::value, "ComponentType must derive from BaseComponent");

            m_components.emplace_back(component);

            return component;
        }

        template <typename ComponentType>
        void RemoveComponent(std::shared_ptr<ComponentType> component)
        {
            static_assert(std::is_base_of<BaseComponent, ComponentType>::value, "ComponentType must derive from BaseComponent");

            auto it = std::remove_if(m_components.begin(), m_components.end(), [](const std::shared_ptr<BaseComponent>& component)
                {
                    return typeid(*component) == typeid(ComponentType);
                });

            if (it != m_components.end())
            {
                m_components.erase(it, m_components.end());
            }
        }

        template <typename ComponentType>
        std::shared_ptr<ComponentType> GetComponent() const
        {
            static_assert(std::is_base_of<BaseComponent, ComponentType>::value, "ComponentType must derive from BaseComponent");

            for (const auto& component : m_components)
            {
                if (typeid(*component) == typeid(ComponentType))
                {
                    return std::static_pointer_cast<ComponentType>(component);
                }
            }
            return nullptr;
        }

        template <typename ComponentType>
        bool HasComponent() const
        {
            static_assert(std::is_base_of<BaseComponent, ComponentType>::value, "ComponentType must derive from BaseComponent");

            return std::any_of(m_components.begin(), m_components.end(), [](const std::shared_ptr<BaseComponent>& component)
                {
                    return typeid(*component) == typeid(ComponentType);
                });
        }


        //void SetParent(GameObject* parent)
        //{
        //    if (parent == this || IsChild(parent))
        //    {
        //        return;
        //    }

        //    //if (parent == nullptr)
        //    //    SetLocalPosition(GetWorldPosition());
        //    //else
        //    //{
        //    //    if (keepWorldPosition)
        //    //        SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
        //    //    SetPositionDirty()
        //    //}

        //    if (m_parent)
        //    {
        //        m_parent->RemoveChild(this);
        //    }

        //    m_parent = parent;

        //    if (m_parent)
        //    {
        //        m_parent->AddChild(this);
        //    }

        //    // Update position, rotation, and scale
        //    // Use dirty flag pattern if necessary
        //}

        //void SetLocalPosition(const glm::vec3& pos)
        //{
        //    m_localPosition = pos;
        //    SetPositionDirty();
        //}


    private:
        //void AddChild(GameObject* child)
        //{
        //    if (child == nullptr || IsParent(child))
        //    {
        //        return;
        //    }

        //    if (child->m_parent)
        //    {
        //        child->m_parent->RemoveChild(child);
        //    }

        //    child->m_parent = this;
        //    m_children.push_back(child);

        //    // Update position, rotation, and scale
        //}

        ////    Can SetParent use AddChild to do its job ?
        ////    Can AddChild use SetParent to do its job ?
        ////    No – stack overflow would happen
        ////    Do we really need AddChild / RemoveChild ?
        ////    No, being able to set the parent on a GameObject is enough.
        ////    Set the parent to nullptr to remove the child from its parent.

        //void RemoveChild(GameObject* child)
        //{
        //    if (child == nullptr || !IsChild(child))
        //    {
        //        return;
        //    }

        //    auto it = std::remove(m_children.begin(), m_children.end(), child);
        //    if (it != m_children.end())
        //    {
        //        m_children.erase(it);
        //    }

        //    child->m_parent = nullptr;

        //    // Update position, rotation, and scale
        //}

        //bool IsChild(GameObject* potentialChild) const
        //{
        //    for (const auto& child : m_children)
        //    {
        //        if (child == potentialChild || child->IsChild(potentialChild))
        //        {
        //            return true;
        //        }
        //    }
        //    return false;
        //}

        //bool IsParent(GameObject* potentialParent) const
        //{
        //    if (m_parent == nullptr)
        //    {
        //        return false;
        //    }

        //    if (m_parent == potentialParent)
        //    {
        //        return true;
        //    }

        //    return m_parent->IsParent(potentialParent);
        //}

        //const glm::vec3& GetWorldPosition()
        //{
        //    if (m_positionIsDirty)
        //        UpdateWorldPosition();
        //    return m_worldPosition;
        //}
        //void UpdateWorldPosition()
        //{
        //    if (m_positionIsDirty)
        //    {
        //        if (m_parent == nullptr)
        //            m_worldPosition = m_localPosition;
        //        else
        //            m_worldPosition = m_parent->GetWorldPosition() + m_localPosition;
        //    }
        //    m_positionIsDirty = false;
        //}

        std::vector<std::shared_ptr<BaseComponent>> m_components;
        std::shared_ptr<Texture2D> m_texture{};
        //GameObject* m_parent{ nullptr };
        //std::vector<GameObject*> m_children;
        //bool m_positionIsDirty{ true };
        Transform m_transform{};
    };
}

