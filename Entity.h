#include  "Components.h"

enum CTag{
	default_tag,
	bullet,
	enemy,
	player,
	enemy_small
};

class Entity{
	size_t m_id = 0;
	CTag m_tag = default_tag;
	bool m_alive = true;
pubic:
	Entity(const size_t id, const CTag tag);

	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CShape> cShape;
	std::shared_ptr<CCollision> cCollision;
	std::shared_ptr<CInput> cInput;
	std::shared_ptr<CScore> cScore;
	std::shared_ptr<CLifeSpan> cLifeSpan;

	size_t id() const;
	CTag& tag() const;
	bool isAlive() const;
	void destroy();
};
