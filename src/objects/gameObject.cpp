#include "gameObject.hpp"
#include "renderer.hpp"

void GameObject::render() {
	if (mClip == -1)
		mAsset->render(mActive, mPosition, mRenderSize);
	else {
		bool reset = mAsset->render(mActive, mPosition, mRenderSize, (int)mClip);
		if (reset) {
			mClip = 0.0f;
			if (mClipResetCount != -1) {
				mClipResetCount -= 1;
				if (mClipResetCount == 0) {
					changeActiveTexture("default", -1, true);
				}
			}
		}
	}
}

void GameObject::changeActiveTexture(std::string name, int resetCount, bool force) {
	if ((mClipResetCount != -1 && resetCount != -1) ||
		(mClipResetCount == -1 && name.compare(mActive) != 0)|| force) {
		mClip = 0.0f;
		mClipResetCount = resetCount;
		mActive = name;
	}
}

GameObject::~GameObject() {
	delete mAsset;
}