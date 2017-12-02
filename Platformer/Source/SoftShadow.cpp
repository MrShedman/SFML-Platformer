#include <SoftShadow.h>
#include <TileMap.h>
#include <LightManager.h>
#include <iostream>
#include <PlayerSprite.h>

SoftShadow::SoftShadow(sf::RenderWindow &window, PlayerSprite &sprite, TileMap &map, LightManager &lManager)
	:
map(map),
lManager(lManager),
window(window),
sprite(sprite),
upScale(1.0f),
lightSize(1280)
{
	shadowMapShader.loadFromFile("Shaders/shadowmap.fsh", sf::Shader::Fragment);
	//shadowMapShader.setUniform("u_texture", sf::Shader::CurrentTexture);
	
	shadowRenderShader.loadFromFile("Shaders/shadowrender.fsh", sf::Shader::Fragment);
	//shadowRenderShader.setUniform("u_texture", sf::Shader::CurrentTexture);

	occludersRT.create(window.getSize().x, window.getSize().y);
	occluders.setTexture(occludersRT.getTexture());
	occluders.setOrigin(occludersRT.getSize().x / 2.f, occludersRT.getSize().y / 2.f);

	shadowMapRT.create(lightSize, 1u);
	shadowMapRT.setRepeated(true);
	shadowMap.setTexture(shadowMapRT.getTexture(), true);
	shadowMap.setOrigin(shadowMapRT.getSize().x / 2.f, shadowMapRT.getSize().y / 2.f);

	finalRT.create(window.getSize().x, window.getSize().y);
	final.setTexture(finalRT.getTexture(), true);
	final.setOrigin(finalRT.getSize().x / 2.f, finalRT.getSize().y / 2.f);

	additive = true;
	softShadows = true;
	softShadows_optimised = true;
}

void SoftShadow::renderBegin(sf::RenderTarget &target, sf::RenderStates states)
{
	if (softShadows_optimised)
	{
		return renderShadows(target, states);
	}

	sf::View viewFinal = target.getView();

	final.setPosition(viewFinal.getCenter());

	finalRT.setView(getAlignedView(viewFinal));

	finalRT.clear();
	
	if (additive)
	{
		states.blendMode = sf::BlendAdd;
	}
	
	std::vector<Light*> lights = map.lightManager.getLights();

	sf::View view = target.getView();
	//view.setSize(static_cast<sf::Vector2f>(occludersRT.getSize()));
	view = getAlignedView(view);
	view.setSize(occludersRT.getSize().x * 1.0f, occludersRT.getSize().y * 1.0f);

	occluders.setPosition(view.getCenter());

	sf::Vector2f pos = view.getCenter() - view.getSize() / 2.f;

	sf::FloatRect rect(pos, view.getSize());

	for (auto &l : lights)
	{
		if (rect.contains(l->getPosition()))
		{
			renderLight(*l, finalRT, states);
		}
	}

	if (additive)
	{
		states.blendMode = sf::BlendAlpha;
	}

	finalRT.draw(map, states);
	finalRT.display();
	
	target.draw(final, states);
}

sf::RenderTarget& SoftShadow::draw()
{
	return occludersRT;
}

void SoftShadow::renderLight(Light &light, sf::RenderTarget &target, sf::RenderStates states, sf::Vector2f cam_pos)
{
	sf::Vector2f pos = light.getPosition() - sf::Vector2f(0, 24);

	sf::View view;// = target.getView();
	view.setSize(sf::Vector2f(lightSize, lightSize));//
	//view.setSize(static_cast<sf::Vector2f>(occludersRT.getSize()));
	view.setCenter(pos);
	view = getAlignedView(view);

	/*
	occludersRT.setView(view);
	occludersRT.clear(sf::Color(0, 0, 0, 0));
	map.drawLights(occludersRT, states);
	occludersRT.draw(sprite, states);
	occludersRT.display();*/

	sf::Vector2f offset = (pos - cam_pos);
	offset.x /= (float)occludersRT.getSize().x;
	offset.y /= (float)occludersRT.getSize().y;
	offset.y = -offset.y;
	//offset.x /= lightSize;
	//offset.y /= lightSize;

	//offset.x += randomize(-0.1f, 0.1f);

	//occluders.setPosition(pos);

	//offset.x = 0.0f;
	//offset.y = 0.0f;

	//std::cout << offset.x << offset.y << std::endl;

	//float f = light.size * randomize(0.9f, 1.0f);
	sf::Vertex m_vertices[4];
	m_vertices[0].position = sf::Vector2f(0, 0);
	m_vertices[1].position = sf::Vector2f(0, lightSize);
	m_vertices[2].position = sf::Vector2f(lightSize, 0);
	m_vertices[3].position = sf::Vector2f(lightSize, lightSize);

	m_vertices[0].texCoords = sf::Vector2f(0, 0);
	m_vertices[1].texCoords = sf::Vector2f(0, lightSize);
	m_vertices[2].texCoords = sf::Vector2f(lightSize, 0);
	m_vertices[3].texCoords = sf::Vector2f(lightSize, lightSize);

	sf::Transformable t;
	t.setPosition(pos);
	t.setOrigin(sf::Vector2f(lightSize / 2, lightSize / 2));

	states.shader = &shadowMapShader;
	shadowMapShader.setUniform("u_texture", *occluders.getTexture());// sf::Shader::CurrentTexture);
	shadowMapShader.setUniform("resolution", sf::Vector2f(lightSize, lightSize));
	shadowMapShader.setUniform("upScale", upScale);
	shadowMapShader.setUniform("offset", offset);

	shadowMapRT.setView(view);
	shadowMapRT.clear(sf::Color(0, 0, 0, 0));	
	//shadowMapRT.draw(occluders, states);
	sf::View v = target.getView();
	//target.setView(view);
	states.texture = shadowMap.getTexture();
	states.transform *= t.getTransform();
	shadowMapRT.draw(m_vertices, 4, sf::TriangleStrip, states);
	//target.setView(v);
	shadowMapRT.display();

	states.shader = &shadowRenderShader;
	shadowRenderShader.setUniform("u_texture", sf::Shader::CurrentTexture);
	shadowRenderShader.setUniform("resolution", sf::Vector2f(lightSize, lightSize));
	shadowRenderShader.setUniform("softShadows", softShadows ? 1.f : 0.f);
	shadowRenderShader.setUniform("offset", sf::Vector2f(0.0f, 0.0f));

	//float sx = occludersRT.getSize().x / shadowMapRT.getSize().x * upScale;
	//float sy = occludersRT.getSize().y / shadowMapRT.getSize().y * upScale;

	float sx = 1.0f;
	float sy = 720;// (float)lightSize;

	shadowMap.setPosition(lightSize/2, lightSize/2);
	shadowMap.setScale(sx, -sy);
	shadowMap.setColor(light.getColor());
	target.draw(shadowMap, states);
}

void SoftShadow::renderShadows(sf::RenderTarget &target, sf::RenderStates states)
{
	sf::View view = getAlignedView(target.getView());

	final.setPosition(view.getCenter());

	finalRT.setView(view);
	finalRT.clear();

	if (additive)
	{
		states.blendMode = sf::BlendAdd;
	}

	// @ToDo batch draw the map to save draw calls
	occludersRT.setView(view);
	occludersRT.clear(sf::Color(0, 0, 0, 0));
	map.drawLights(occludersRT, states);
	occludersRT.draw(sprite, states);
	occludersRT.display();

	std::vector<Light*> lights = map.lightManager.getLights();

	float enlarge = 1.0f;

	view.setSize(occludersRT.getSize().x * enlarge, occludersRT.getSize().y * enlarge);

	occluders.setPosition(view.getCenter());

	sf::Vector2f pos = view.getCenter() - view.getSize() / 2.f;

	sf::FloatRect rect(pos, view.getSize());

	for (auto &l : lights)
	{
		if (rect.contains(l->getPosition()))
		{
			renderLight(*l, finalRT, states, view.getCenter());
		}
	}

	if (additive)
	{
		states.blendMode = sf::BlendAlpha;
	}

	// @ToDo draw occluders then draw non occluders over top
	occluders.setPosition(view.getCenter());
	//finalRT.draw(occluders, states);
	finalRT.draw(map, states);
	finalRT.display();

	target.draw(final, states);
}

void SoftShadow::renderLight(Light &light, sf::RenderTarget &target, sf::RenderStates states)
{
	int rp = 5;
	sf::Vector2f pos = light.getPosition() + sf::Vector2f(randomize(-rp, rp), randomize(0, rp));

	sf::View view = target.getView();
	view.setSize(static_cast<sf::Vector2f>(occludersRT.getSize()));
	view.setCenter(pos);
	view = getAlignedView(view);

	occludersRT.setView(view);
	occludersRT.clear(sf::Color(0, 0, 0, 0));
	map.drawLights(occludersRT, states);
	occludersRT.draw(sprite, states);
	occludersRT.display();

	occluders.setPosition(pos);

	float f = light.size * randomize(0.9f, 1.0f);

	states.shader = &shadowMapShader;
	shadowMapShader.setUniform("resolution", sf::Vector2f(lightSize, lightSize));
	shadowMapShader.setUniform("upScale", f);// upScale);

	shadowMapRT.setView(view);
	shadowMapRT.clear(sf::Color(0, 0, 0, 0));
	shadowMapRT.draw(occluders, states);
	shadowMapRT.display();

	states.shader = &shadowRenderShader;
	shadowRenderShader.setUniform("resolution", sf::Vector2f(lightSize, lightSize));
	shadowRenderShader.setUniform("softShadows", softShadows ? 1.f : 0.f);

	float sx = occludersRT.getSize().x / (float)lightSize * f;//upScale;
	float sy = occludersRT.getSize().y * f;//upScale;

	shadowMap.setPosition(pos);
	shadowMap.setScale(sx, -sy);
	shadowMap.setColor(light.getColor());
	target.draw(shadowMap, states);
}