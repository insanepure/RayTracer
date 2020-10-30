#ifndef _SCENE_H_
#define _SCENE_H_

#include "window.h"
#include "camera.h"
#include "iobject.h"
#include "ilight.h"

#include <vector>
#include <thread>
#include <atomic>

///Forward declarations
struct SDL_Texture;

/// @brief Whole Scene which contains all Spheres, Lights etc
///
class CScene
{

private:
    enum { Threads = 4,JobsVertical=8,JobsHorizontal=8,JobCount=JobsVertical*JobsHorizontal };

	/// @brief Jobs the Threads can have
	///
    struct SJob
    {
        unsigned int minX;
        unsigned int minY;
        unsigned int maxX;
        unsigned int maxY;
    };

	/// @brief The BackBuffer, which is drawn to
	///
    SDL_Texture* m_pTexture;
	/// @brief Window Pointer to access it directly within the Scene
	///
    const CWindow* m_pWindow;
	/// @brief Array to store our Pixels during rendering
	///
    int* m_pPixelBuffer; 
	/// @brief Size of a line in the Backbuffer
	///
    int m_TexturePitch; 
	/// @brief Width of the Texture
	///
	unsigned int m_Width;
	/// @brief Height of the Texture
	///
	unsigned int m_Height;
	/// @brief Camera where the Rays come from
	///
    /// @remarks Default Values are the Data defined in SceneData
    ///
    CCamera m_Camera;
	/// @brief All objects within the Scene
	///
    std::vector<IObject*> m_Objects;
	/// @brief All lights within the Scene
	///
    std::vector<ILight*> m_Lights;
	/// @brief Worker Threads
	///
    std::thread* m_pThreads[Threads-1];
	/// @brief Jobs to work on
	///
    SJob m_Jobs[JobCount];
	/// @brief next Job to Do
	///
    std::atomic<int> m_NextJob;
	/// @brief Amount of Done Jobs
	///
    std::atomic<int> m_DoneJobs;
	/// @brief Bool to end all Threads
	///
    bool m_End;
	/// @brief true for Antialiasing, false for not
	///
    bool m_AntiAliasing;
public:
	/// @brief Constructor to initialize a Scene
	///
	/// @param Reference to the Window
	/// @param Width of the Texture
	/// @param Height of the Texture
	////
	CScene(const CWindow& a_rWindow,const unsigned int a_Width,const unsigned int a_Height);

	/// @brief Destructor to destroy a Scene
	///
	~CScene();

public:
	/// @brief Return the Camera
    ///
    /// @returns a reference to the Camera
	////
    const CCamera& GetCamera() const;
	/// @brief Return the LightVector
    ///
    /// @returns a reference to the LightVector
	////
    const std::vector<ILight*>& GetLights() const;
	/// @brief Do a RayTracing against the Scene
	///
	/// @param Ray to Test with the Scene
    /// @param Hit Information we get back, nullptr if no informations needed
    /// @param maximal Distance of the Ray
    ///
    /// @returns the hit Object or nullptr if none
    ///
    IObject* Trace(const CRay& a_rViewRay, SHit* a_pHit,float a_Distance) const;
	/// @brief Add an Object to the Scene
	///
	/// @param Object to add
    ///
    void AddObject(IObject* a_pObject);
	/// @brief Add a Light to the Scene
	///
	/// @param Light to add
    ///
    void AddLight(ILight* a_pLight);
	/// @brief Render the whole Scene
    ///
    /// @param Whether AntiAliasing should be used or not
	///
    void Render(bool a_AntiAliasing);
private:
	/// @brief "Loop" for the Thread, to do work
    ///
    /// @param Scene to use
	///
    static void DoWork(CScene* a_pSelf);
	/// @brief Get a Job if there is one
    ///
    /// @returns true if he has a job, false if not
	///
    bool GetJob();
	/// @brief Do the Job
    ///
    /// @param Index of the Job to Do
	///
    void ProcessJob(int a_Index);
};

#endif /* _SCENE_H_ */