#pragma once

namespace dae
{
    class GameObject;

    class BaseComponent
    {
    public:
        BaseComponent() = default;
        virtual ~BaseComponent() = default;

        BaseComponent(const BaseComponent& other) = delete;
        BaseComponent(BaseComponent&& other) = delete;
        BaseComponent& operator=(const BaseComponent& other) = delete;
        BaseComponent& operator=(BaseComponent&& other) = delete;

        virtual void Update(float delta_time) = 0;
        virtual void Render() const = 0;

        void SetOwner(GameObject* owner) { m_Owner = owner; }
        GameObject* GetOwner() const { return m_Owner; }

    protected:
        GameObject* m_Owner{ nullptr };
    };
}
