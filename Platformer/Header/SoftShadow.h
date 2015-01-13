#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class TileMap;
class LightManager;
class Light;
class PlayerSprite;

class SoftShadow
{
public:

	SoftShadow(sf::RenderWindow &window, PlayerSprite &sprite, TileMap &map, LightManager &lManager);

	void renderBegin(sf::RenderTarget &target, sf::RenderStates states);

	void renderEnd(sf::RenderTarget &target, sf::RenderStates states);

	void renderLight(Light &light, sf::RenderTarget &target, sf::RenderStates states);

	sf::RenderTarget& draw();

private:

	PlayerSprite &sprite;

	sf::View origninalView;

	bool additive;
	bool softShadows;

	const float upScale = 1.f;
	const unsigned int lightSize = 256u;

	sf::Shader shadowMapShader;
	sf::Shader shadowRenderShader;

	sf::Sprite occluders;
	sf::Sprite shadowMap;
	sf::Sprite final;
	sf::RenderTexture occludersRT;
	sf::RenderTexture shadowMapRT;
	sf::RenderTexture finalRT;

	TileMap &map;
	LightManager &lManager;
	sf::RenderWindow &window;
};