#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include "stdafx.h"
#include "Mesh.h"
#include "Object.h"
#include "Shader.h"



class CResource{
public:
	CResource() : m_MeshId(-1), m_TextureId(-1), m_MaterialId(-1), m_ShaderId(-1) {}
	~CResource() {}

	/*	========================================================================
	*	�ش� ���ҽ��� � ��ǰ?�� ����� �� �����Ѵ�
	*	\remarks ������� �ʴ´ٸ� -1		*/
	void SetIDs(BYTE meshID, BYTE textureID, BYTE materialID, BYTE shaderID);

	BYTE GetMeshID() { return m_MeshId; }
	BYTE GetTextureID() { return m_TextureId; }
	BYTE GetMaterialID() { return m_MaterialId; }
	BYTE GetShaderID() { return m_ShaderId; }

private:
	BYTE m_MeshId;
	BYTE m_TextureId;
	BYTE m_MaterialId;
	BYTE m_ShaderId;
};


class CResourceManager
{
public:
	enum class ResourceType : BYTE{
		START = 0,
		Cube = 0,
		END
	};
	enum class ShaderType : BYTE{
		START = 0,
		IlluminatedTextured = 0,
		END
	};

	CMesh* GetMesh(ResourceType type);
	CTexture* GetTexture(ResourceType type);
	CMaterial* GetMaterial(ResourceType type);
	CShader* GetShader(ResourceType type);

	bool IsTextureEnable(ResourceType type);
	bool IsMaterialEnable(ResourceType type);

	CResourceManager* GetSingleton(ID3D11Device *pd3dDevice);

	~CResourceManager();

private:
	CResourceManager(ID3D11Device *pd3dDevice);

	std::vector<CResource*> m_vResources;

	std::map<BYTE, CMesh*> m_mMesh;
	std::map<BYTE, CTexture*> m_mTexture;
	std::map<BYTE, CMaterial*> m_mMaterial;
	std::map<BYTE, CShader*> m_mShader;

	void _LoadMesh(ID3D11Device *pd3dDevice);
	void _LoadTextures(ID3D11Device *pd3dDevice);
	void _LoadMaterials();
	void _CreateShaders(ID3D11Device *pd3dDevice);
};





#endif