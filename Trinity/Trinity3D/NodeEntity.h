#pragma once

#ifndef PLATFORM_WIN32
#    define PLATFORM_WIN32 1
#endif

#include "Node3D.h"
#include "Mesh3D.h"
// 
//#include "SmartMesh.h"
#include "PhysicsBody.h"
#include "PBBox.h"
#include "PBSphere.h"
#include "PBConvex.h"
#include "PBCapsule.h"



        enum PhysicsType {
            Static, Box, Sphere, Capsule, Convex, Mesh
        };

        /// <summary>
        /// A NodeEntity is a 3D node, that contains a single or multiple meshes, binded to the node, and rendered
        /// at the nodes position and rotation, with it's scale.
        /// </summary>
        class NodeEntity :
            public Node3D
        {
        public:

            /// <summary>
            /// The base constructor will create an empty entity with no meshes attached.
            /// </summary>
            NodeEntity();


            Node3D* Clone();

            /// <summary>
            /// Adds a mesh to the entity, whenever rendered, this mesh will be rendered also.
            /// </summary>
            /// <param name="mesh"></param>
            void AddMesh(Mesh3D* mesh);

            /// <summary>
            /// Returns a list of this node's meshes. These are the actual meshes, not a copy or reference. 
            /// </summary>
            /// <returns></returns>
            std::vector<Mesh3D*> GetMeshes();

            void RenderDepth();
            /// <summary>
            /// Renders the entity
            /// </summary>
            void Render();
            /// <summary>
            /// Internal use.
            /// </summary>
            void RenderSmartMesh();

            //This converts a whole entity into a single draw call, using bindless textures. max of 1024 unique textures per  smart mesh.
            void ConvertToSmartMesh();


            void SetChanged() {
                for (int i = 0; i < mMeshes.size(); i++) {
                    mMeshes[i]->SetChanged();
                }
                for (int i = 0; i < mChildren.size(); i++) {
               //     mChildren[i]->SetChanged();
                }
            }
            /// <summary>
            /// Returns the given mesh of the entity.
            /// </summary>
            /// <param name="i"></param>
            /// <returns></returns>
            Mesh3D* GetMesh(int i);
            /// <summary>
            /// Sets the physics collision to a box, wrapped around the entity.
            /// </summary>
            void SetPhysicsBox();
            void SetPhysicsBoxSize(float size);
            /// <summary>
            /// Sets the physics collision to a sphere, wrapped around the entity.
            /// </summary>
            void SetPhysicsSphere();
            /// <summary>
            /// Sets the physics collision to a automatically generated convex hull
            /// </summary>
            void SetPhysicsConvex();
            /// <summary>
            /// sets the physics collision to a capsule.
            /// </summary>
            void SetPhysicsCapsule();
            void SetPhysicsCapsuleSize(float height, float width);
            /// <summary>
            /// returns the smallest possible bounding box around the mesh.
            /// </summary>
            /// <returns></returns>
            float3 GetBounds();
            /// <summary>
            /// Constrain physics on any given dimension.
            /// </summary>
            /// <param name="x"></param>
            /// <param name="y"></param>
            /// <param name="z"></param>
            void SetConstraint(bool x, bool y, bool z);
            /// <summary>
            /// Internal use.
            /// </summary>
            void UpdatePhysics();
            /// <summary>
            /// Sets the position of a node.
            /// </summary>
            /// <param name="position"></param>
            void SetPosition(float3 position);
            /// <summary>
            /// Sets the euler rotation of the node.
            /// </summary>
            /// <param name="pitch"></param>
            /// <param name="yaw"></param>
            /// <param name="roll"></param>
            void SetRotation(float pitch, float yaw, float roll);
            /// <summary>
            /// Sets the physics collision to a per tri map of the mesh. This is useful for level collisions, as the tri mesh varient can not move.
            /// </summary>
            void SetPhysicsTris();


        

         

      

           


            void UpdateRotation() {

                if (mBody == NULL) return;
                mBody->SetRotation(GetRotation());

            }

            PhysicsBody* GetBody() {
                return nullptr;
            }

            void Move(float3 move) {

                Node3D::Move(move);
                if (mBody == NULL) return;

                mBody->SetPosition(mPosition);

            }


            PhysicsType GetPhysicsType() {
                return mPType;
            }
            void SetPhysicsType(PhysicsType type)
            {
                mPType = type;
            }

            void ClearPhysics() {


                if (mTriBody != nullptr) {
                    mTriBody->Remove();
                }
                if (mBody != nullptr) {
                    mBody->Remove();
                }

            }

            void SaveMaterials(std::string path) {

                int a = 5;


                for (int i = 0; i < mMeshes.size(); i++) {

                    std::string out = path + mName + "_Mesh" + std::to_string(i) + ".vmat";
                    auto mat = mMeshes[i]->GetMaterial();
                    mat->SaveMaterial(out);
                    mMeshes[i]->SetMaterialPath(out);

                }
                for (int i = 0; i < mChildren.size(); i++) {

                    mChildren[i]->SaveMaterials(path);

                }


            }

            void ReloadMaterials() {

                for (int i = 0; i < mMeshes.size(); i++) {

                    auto mp = mMeshes[i]->GetMaterial()->GetPath();

                    Material* mat = new Material;
                    mat->LoadMaterial(mp);
                    mMeshes[i]->SetMaterial(mat);
                    

                }

                for (int i = 0; i < mChildren.size(); i++) {

                    mChildren[i]->ReloadMaterials();

                }

            }

        protected:
            PhysicsBody* mBody = nullptr;
            PhysicsBody* mTriBody = nullptr;
            /// <summary>
            /// A list containing all of this NodeEntity's attached meshes.
            /// </summary>
            std::vector<Mesh3D*> mMeshes;
            // SmartMesh* mSmartMesh;
            PhysicsType mPType = PhysicsType::Static;
            // static Kinetic::FX::Effect* FXSmartMesh;



        };


