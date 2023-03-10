#include "Prerrequisitos.h"
#pragma once

class
	DeviceContext {
public:
	DeviceContext() = default;
	~DeviceContext() {SAFE_RELEASE(m_deviceContext);}

	void
	init();

	void
	update();

	void
	render();

	void
	destroy();

private:
	ID3D11DeviceContext* m_deviceContext = nullptr;
};