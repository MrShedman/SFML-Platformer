#include <Container.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{

Container::Container()
: mChildren()
, mSelectedChild(-1)
{
}

void Container::pack(Component::Ptr component)
{
	mChildren.push_back(component);
}

void Container::handleEvent(const sf::Event& event)
{
	for (auto &child : mChildren)
	{
		child->handleEvent(event);
	}
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

	for (auto &child : mChildren)
	{
		target.draw(*child, states);
	}
}

}