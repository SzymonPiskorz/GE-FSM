#include <AnimatedSprite.h>

AnimatedSprite::AnimatedSprite() : 
	m_current_frame(0),
	m_time(0.5f),
	m_loop(true),
	m_play_count(0),
	m_max_plays(0),
	m_played(false),
	m_texture(nullptr),
	m_rec(),
	m_textureHeight(),
	m_textureWidth()
{
	DEBUG_MSG("AnimatedSprite()");
}

AnimatedSprite::AnimatedSprite(SDL_Texture* t) : AnimatedSprite(){
	DEBUG_MSG("AnimatedSprite(const Texture&)");
	this->setTexture(t);
}

AnimatedSprite::AnimatedSprite(SDL_Texture* t,SDL_Rect rect) : 
	AnimatedSprite(t)
{
	DEBUG_MSG("AnimatedSprite(const Texture&, const IntRect&)");
	m_frames.push_back(rect);
}

AnimatedSprite::~AnimatedSprite() {
	DEBUG_MSG("~AnimatedSprite()");
}

void AnimatedSprite::setTexture(SDL_Texture* t_tex)
{
	m_texture = t_tex;
}

const Clock& AnimatedSprite::getClock()
{
	return m_clock;
}

float AnimatedSprite::getTime()
{
	return m_time;
}

void AnimatedSprite::setTime(float t)
{
	this->m_time = t;
}

const vector<SDL_Rect>& AnimatedSprite::getFrames() {
	return m_frames;
}

void AnimatedSprite::clearFrames() {
	m_current_frame = 0;
	m_played = false;
	if (!m_frames.empty())
	{
		m_frames.clear();
	}
}

const SDL_Rect& AnimatedSprite::getFrame(int n) {
	return m_frames[n];
}

void AnimatedSprite::addFrame(const SDL_Rect& frame) {
	m_frames.push_back(frame);
}

const int AnimatedSprite::getCurrentFrame() {
	return m_current_frame;
}

void AnimatedSprite::setLooped(bool loop) {
	this->m_loop = loop;
}

const bool AnimatedSprite::getLooped() {
	return this->m_loop;
}

void AnimatedSprite::setPlayed(bool played) {
	this->m_played = played;
}

const bool AnimatedSprite::getPlayed() {
	return this->m_played;
}

void AnimatedSprite::update(){
	// If not looped only play once
	if (m_played == true && !m_loop)
	{
		m_current_frame = m_frames.size() - 1;
	}
	else {
		if (m_clock.getElapsedTimeAsSeconds() > m_time) {
			if (m_frames.size() > m_current_frame + 1)
			{
				m_current_frame++;
			}
			else {
				m_current_frame = 0;
				m_played = true;
			}
			m_clock.restart();
		}
	}
	
}

void AnimatedSprite::setTextureRect(SDL_Rect t_rec)
{
	m_rec = t_rec;
}

void AnimatedSprite::render(int t_x, int t_y, SDL_Renderer* t_renderer)
{
	SDL_Rect render = {t_x, t_y, m_rec.w, m_rec.h};
	SDL_RenderCopy(t_renderer, m_texture, &m_rec, &render);
}

