
#include"main.h"
#include "collision.h"

list<Collider*> Collision::m_Circle;
list<Collider*> Collision::m_Box;

bool Collision::HitCheckCircle(Collider* hit, Collider* washit)
{
    float r = (hit->GetRadius() + washit->GetRadius()) * (hit->GetRadius() + washit->GetRadius());
    Vector3 vec = washit->GetPosition() - hit->GetPosition();
    return vec.LengthSpr() < r;
}

bool Collision::HitCheckBox(Collider* hit, Collider* washit)
{

    Vector3 posA{}, posB{};
    float sizeA{}, sizeB{};

    posA = hit->GetPosition();
    posB = washit->GetPosition();

    sizeA = hit->GetRadius();
    sizeB = washit->GetRadius();

	float minXA = posA.x - sizeA * 0.5f;
	float maxXA = posA.x + sizeA * 0.5f;
	float minYA = posA.y - sizeA * 0.5f;
	float maxYA = posA.y + sizeA * 0.5f;
	float minZA = posA.z - sizeA * 0.5f;
	float maxZA = posA.z + sizeA * 0.5f;

	float minXB = posB.x - sizeB * 0.5f;
	float maxXB = posB.x + sizeB * 0.5f;
	float minYB = posB.y - sizeB * 0.5f;
	float maxYB = posB.y + sizeB * 0.5f;
	float minZB = posB.z - sizeB * 0.5f;
	float maxZB = posB.z + sizeB * 0.5f;

	if (minXB < maxXA) {

		if (maxXB > minXA) {

			if (minYB < maxYA) {

				if (maxYB > minYA) {

					if (minZB < maxZA) {

						if (maxZB > minZA) {
							return true;
						}

					}

				}

			}

		}

	}

    return false;
}

void Collision::OnCollisionEnter()
{

	for (auto& hit : m_Circle) {

		for (auto& washit : m_Circle) {

			if (hit != washit) {

				if (HitCheckCircle(hit, washit)) {

					hit->OnCollisionEnter(washit->GetGameObject());
					washit->OnCollisionEnter(hit->GetGameObject());

				}

			}

		}

	}

	for (auto& hit : m_Box) {

		for (auto& washit : m_Box) {

			if (hit != washit) {

				if (HitCheckBox(hit, washit)) {

					hit->OnCollisionEnter(washit->GetGameObject());
					washit->OnCollisionEnter(hit->GetGameObject());

				}

			}

		}

	}

	for (auto& hit : m_Circle) {

		for (auto& washit : m_Box) {

			if (HitCheckBox(hit, washit)) {

				hit->OnCollisionEnter(washit->GetGameObject());
				washit->OnCollisionEnter(hit->GetGameObject());

			}

		}

	}

}

void Collision::OnCollisionExit()
{

	for (auto& hit : m_Circle) {

		for (auto& washit : m_Circle) {

			if (hit != washit) {

				if (!HitCheckCircle(hit, washit)) {

					hit->OnCollisionExit(washit->GetGameObject());
					washit->OnCollisionExit(hit->GetGameObject());

				}

			}

		}

	}

	for (auto& hit : m_Box) {

		for (auto& washit : m_Box) {

			if (hit != washit) {

				if (!HitCheckBox(hit, washit)) {

					hit->OnCollisionExit(washit->GetGameObject());
					washit->OnCollisionExit(hit->GetGameObject());

				}

			}

		}

	}

	for (auto& hit : m_Circle) {

		for (auto& washit : m_Box) {

			if (!HitCheckBox(hit, washit)) {

				hit->OnCollisionExit(washit->GetGameObject());
				washit->OnCollisionExit(hit->GetGameObject());

			}

		}

	}

}

void Collision::Update()
{
    OnCollisionEnter();
    OnCollisionExit();

	m_Circle.remove_if([](Collider* collider) { return collider->GetDestroy(); });
	m_Box.remove_if([](Collider* collider) { return collider->GetDestroy(); });

}

void Collision::Uninit()
{

	m_Circle.clear();
	m_Box.clear();

}

void Collision::SetCircleCollider(Collider* collider)
{
    m_Circle.push_back(collider);
}

void Collision::SetBoxCollider(Collider* collider)
{
    m_Box.push_back(collider);
}
