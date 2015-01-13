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
upScale(1.f),
lightSize(1024)
{
	shadowMapShader.loadFromFile("Shaders/shadowmap.fsh", sf::Shader::Fragment);
	shadowMapShader.setParameter("u_texture", sf::Shader::CurrentTexture);
	
	shadowRenderShader.loadFromFile("Shaders/shadowrender.fsh", sf::Shader::Fragment);
	shadowRenderShader.setParameter("u_texture", sf::Shader::CurrentTexture);

	occludersRT.create(window.getSize().x, window.getSize().y);
	occluders.setTexture(occludersRT.getTexture());
	occluders.setOrigin(occludersRT.getSize().x / 2.f, occludersRT.getSize().y / 2.f);

	shadowMapRT.create(lightSize, 1u);
	shadowMap.setTexture(shadowMapRT.getTexture());
	shadowMap.setOrigin(lightSize / 2.f, 0.5f);

	finalRT.create(window.getSize().x, window.getSize().y);
	final.setTexture(finalRT.getTexture());
	final.setOrigin(finalRT.getSize().x / 2.f, finalRT.getSize().y / 2.f);

	additive = true;
	softShadows = true;
}

void SoftShadow::renderBegin(sf::RenderTarget &target, sf::RenderStates states)
{
	//lManager.draw(target);//sf::Color(64, 64, 64, 255));

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

	occludersRT.setView(view);
	occludersRT.clear(sf::Color(0, 0, 0, 0));
	map.drawLights(occludersRT, states);
	occludersRT.draw(sprite, states);
	occludersRT.display();

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
	//lManager.draw(target);
}

sf::RenderTarget& SoftShadow::draw()
{
	return occludersRT;
}

void SoftShadow::renderLight(Light &light, sf::RenderTarget &target, sf::RenderStates states)
{
	sf::Vector2f pos = light.getPosition();
	
	sf::View view = target.getView();
	//view.setSize(lightSize, lightSize);
	sf::Vector2f oldCenter = view.getCenter();
	view.setCenter(pos);
	view = getAlignedView(view);
	
	sf::Vector2f offset;
	offset.x = (1.f / window.getSize().x) * (pos.x - oldCenter.x);
	offset.y = (1.f / window.getSize().y) * (pos.y - oldCenter.y);

	states.shader = &shadowMapShader;
	shadowMapShader.setParameter("resolution", lightSize, lightSize);
	shadowMapShader.setParameter("upScale", upScale);
	shadowMapShader.setParameter("offset", offset);

	shadowMapRT.setView(view);
	shadowMapRT.clear(sf::Color(0, 0, 0, 0));
	shadowMapRT.draw(occluders, states);
	shadowMapRT.display();

	states.shader = &shadowRenderShader;
	shadowRenderShader.setParameter("resolution", lightSize, lightSize);
	shadowRenderShader.setParameter("softShadows", softShadows ? 1.f : 0.f);
	shadowRenderShader.setParameter("offset", offset);

	float finalSize = lightSize * upScale;
	
	shadowMap.setPosition(pos);
	shadowMap.setScale(upScale, -(finalSize));
	shadowMap.setColor(light.getColor());
	target.draw(shadowMap, states);

	//view.setViewport(sf::FloatRect(0,0,1,1));
}


/*
void SoftShadow::renderLight(Light &light, sf::RenderTarget &target, sf::RenderStates states)
{
sf::Vector2f pos = light.getPosition();

sf::View view = target.getView();
view.setSize(static_cast<sf::Vector2f>(occludersRT.getSize()));
view.setCenter(pos);
view = getAlignedView(view);

occludersRT.setView(view);
occludersRT.clear(sf::Color(0, 0, 0, 0));
//map.drawLights(occludersRT, states);
occludersRT.draw(sprite, states);
occludersRT.display();

occluders.setPosition(pos);

states.shader = &shadowMapShader;
shadowMapShader.setParameter("resolution", lightSize, lightSize);
shadowMapShader.setParameter("upScale", upScale);

shadowMapRT.setView(view);
shadowMapRT.clear(sf::Color(0, 0, 0, 0));
shadowMapRT.draw(occluders, states);
shadowMapRT.display();

states.shader = &shadowRenderShader;
shadowRenderShader.setParameter("resolution", lightSize, lightSize);
shadowRenderShader.setParameter("softShadows", softShadows ? 1.f : 0.f);

float finalSize = lightSize * upScale;

shadowMap.setPosition(pos);
shadowMap.setScale(1.f * upScale, -(finalSize));
shadowMap.setColor(light.getColor());
target.draw(shadowMap, states);
}*/