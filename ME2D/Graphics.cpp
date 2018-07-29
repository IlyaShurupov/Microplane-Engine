//============================================================================
// Microplane Engine - ME2D
//----------------------------------------------------------------------------
// Copyright (c) 2018 Ivan Kmeťo
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//	  claim that you wrote the original software. If you use this software
//	  in a product, an acknowledgment in the product documentation would be
//	  appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//	  misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//
//============================================================================

#include "stdafx.h"
#include "Graphics.h"


Graphics::Graphics()
{
	factory = NULL;
	renderTarget = NULL;
	brush = NULL;
	fillBrush = NULL;
}

Graphics::~Graphics()
{
	if (fillBrush) fillBrush->Release();
	if (brush) brush->Release();
	if (renderTarget) renderTarget->Release();
	if (factory) factory->Release();
}

bool Graphics::Init(HWND windowHandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	res = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)), &renderTarget);
	if (res != S_OK) return false;

	res = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
	if (res != S_OK) return false;

	res = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &fillBrush);
	if (res != S_OK) return false;

	return true;
}


void Graphics::ClearScreen(float r, float g, float b)
{
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}


//-----------------------------------------------[OBJECTS: 2D GEOMETRY]-----------------------------------------------

void Graphics::RenderCircleRGBA(float x, float y, float radius, float r, float g, float b, float a, float strokesize) {
	brush->SetColor(D2D1::ColorF(r, g, b, a));

	D2D1_ELLIPSE circle = D2D1::Ellipse(
		D2D1::Point2F(x, y),
		radius,
		radius
	);
	renderTarget->DrawEllipse(circle, brush, strokesize);
}

void Graphics::RenderCircleRGBAF(float x, float y, float radius, float r, float g, float b, float a, float strokesize, float fill_r, float fill_g, float fill_b, float fill_a) {
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	fillBrush->SetColor(D2D1::ColorF(fill_r, fill_g, fill_b, fill_a));

	D2D1_ELLIPSE circle = D2D1::Ellipse(
		D2D1::Point2F(x, y),
		radius,
		radius
	);
	renderTarget->DrawEllipse(circle, brush, strokesize);
	renderTarget->FillEllipse(circle, fillBrush);
}


void Graphics::RenderEllipseRGBA(float x, float y, float xRadius, float yRadius, float r, float g, float b, float a, float strokesize) {
	brush->SetColor(D2D1::ColorF(r, g, b, a));

	D2D1_ELLIPSE ellipse = D2D1::Ellipse(
		D2D1::Point2F(x, y),
		xRadius,
		yRadius
	);
	renderTarget->DrawEllipse(ellipse, brush, strokesize);
}


void Graphics::RenderSquareRGBA(float x, float y, float size, float r, float g, float b, float a, float strokesize) {
	brush->SetColor(D2D1::ColorF(r, g, b, a));

	D2D1_RECT_F square = D2D1::RectF(
		x - (size / 2),
		y - (size / 2),
		x + (size / 2),
		y + (size / 2)
	);
	renderTarget->DrawRectangle(square, brush, strokesize);
}

void Graphics::RenderSquareRGBAF(float x, float y, float size, float r, float g, float b, float a, float strokesize, float fill_r, float fill_g, float fill_b, float fill_a) {
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	fillBrush->SetColor(D2D1::ColorF(fill_r, fill_g, fill_b, fill_a));

	D2D1_RECT_F square = D2D1::RectF(
		x - (size / 2),
		y - (size / 2),
		x + (size / 2),
		y + (size / 2)
	);
	renderTarget->DrawRectangle(square, brush, strokesize);
	renderTarget->FillRectangle(square, fillBrush);
}
