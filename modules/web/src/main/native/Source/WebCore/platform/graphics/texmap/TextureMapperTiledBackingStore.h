/*
 Copyright (C) 2013 Nokia Corporation and/or its subsidiary(-ies)

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Library General Public
 License as published by the Free Software Foundation; either
 version 2 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Library General Public License for more details.

 You should have received a copy of the GNU Library General Public License
 along with this library; see the file COPYING.LIB.  If not, write to
 the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 Boston, MA 02110-1301, USA.
 */

#ifndef TextureMapperTiledBackingStore_h
#define TextureMapperTiledBackingStore_h

#if USE(TEXTURE_MAPPER)

#include "FloatRect.h"
#include "Image.h"
#include "TextureMapperBackingStore.h"
#include "TextureMapperTile.h"
#include <wtf/RefPtr.h>

namespace WebCore {

class TextureMapper;

class TextureMapperTiledBackingStore : public TextureMapperBackingStore {
public:
    static PassRefPtr<TextureMapperTiledBackingStore> create() { return adoptRef(new TextureMapperTiledBackingStore); }
    virtual ~TextureMapperTiledBackingStore() { }

    virtual RefPtr<BitmapTexture> texture() const override;
    virtual void paintToTextureMapper(TextureMapper&, const FloatRect&, const TransformationMatrix&, float) override;
    virtual void drawBorder(TextureMapper&, const Color&, float borderWidth, const FloatRect&, const TransformationMatrix&) override;
    virtual void drawRepaintCounter(TextureMapper&, int repaintCount, const Color&, const FloatRect&, const TransformationMatrix&) override;

    void updateContentsScale(float);
    void updateContentsSize(const FloatSize&);

    void updateContents(TextureMapper&, Image*, const FloatRect& visibleRect, const IntRect& dirtyRect, BitmapTexture::UpdateContentsFlag);
    void updateContents(TextureMapper&, GraphicsLayer*, const FloatRect& visibleRect, const IntRect& dirtyRect, BitmapTexture::UpdateContentsFlag);

    void setContentsToImage(Image* image) { m_image = image; }

private:
    TextureMapperTiledBackingStore() { }

    void createOrDestroyTilesIfNeeded(const FloatRect& visibleRect, const IntSize& tileSize, bool hasAlpha);
    void updateContentsFromImageIfNeeded(TextureMapper&);
    TransformationMatrix adjustedTransformForRect(const FloatRect&);

    Vector<TextureMapperTile> m_tiles;
    FloatSize m_contentsSize;
    FloatRect m_visibleRect;
    FloatRect m_scaledvisibleRect;
    RefPtr<Image> m_image;
    float m_contentsScale { 1 };
    bool m_isScaleDirty { false };
    bool m_isSizeDirty { false };
};

} // namespace WebCore
#endif

#endif
