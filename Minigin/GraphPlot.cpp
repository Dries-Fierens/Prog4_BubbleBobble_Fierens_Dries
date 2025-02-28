#include "GraphPlot.h"
#include <imgui.h>
#include <chrono>
#include <include/imgui_plot.h>
#include <algorithm>

using namespace std::chrono;

struct transform {
	float matrix[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
};

class GameObject3D {
public:
	transform local;
	int id{};
};

class GameObject3DAlt {
public:
	transform* local;
	int id;
};

void ConfigurePlot(const std::vector<float>& timings, const std::vector<float>& timesteps, ImU32 color, const char* label) {
	auto min = std::min_element(timings.begin(), timings.end());
	auto max = std::max_element(timings.begin(), timings.end());
	ImGui::PlotConfig conf;
	conf.values.xs = timesteps.data();
	conf.values.ys = timings.data();
	conf.values.color = color;
	conf.values.count = static_cast<int>(timings.size());
	conf.scale.min = *min;
	conf.scale.max = *max;
	conf.tooltip.show = true;
	conf.tooltip.format = "x=%.2f, y=%.2f";
	conf.grid_x.show = true;
	conf.grid_y.show = true;
	conf.frame_size = ImVec2(200, 100);
	conf.line_thickness = 1.f;

	ImGui::Plot(label, conf);
}

void dae::GraphPlot::PlotIntegers() const  
{  
	ImGui::Begin("Exercise 1");  

	static std::vector<float> timings;

    ImGui::InputInt("Samples", m_samplesInt.get());

	if (ImGui::Button("Thrash the cache")) 
		timings = GetTimings<int>(*m_samplesInt.get());

	if (!timings.empty()) {
		ConfigurePlot(timings, TIMESTEPS, IM_COL32(125, 125, 0, 255), "Integers");
	}  

	ImGui::End();  
}

void dae::GraphPlot::PlotGameObject3D() const
{
	ImGui::Begin("Exercise 2");

	static std::vector<float> timingsGameObject3D;
	static std::vector<float> timingsGameObject3DAlt;

	ImGui::InputInt("Samples", m_samplesGameObject3D.get());

	if (ImGui::Button("Thrash the cache with GameObject3D"))
		timingsGameObject3D = GetTimings<GameObject3D>(*m_samplesGameObject3D.get());

	if (!timingsGameObject3D.empty())
		ConfigurePlot(timingsGameObject3D, TIMESTEPS, IM_COL32(255, 0, 0, 255), "GameObject3D");

	if (ImGui::Button("Thrash the cache with GameObject3DAlt")) 
		timingsGameObject3DAlt = GetTimings<GameObject3DAlt>(*m_samplesGameObject3D.get());

	if (!timingsGameObject3DAlt.empty())
		ConfigurePlot(timingsGameObject3DAlt, TIMESTEPS, IM_COL32(0, 255, 0, 255), "GameObject3DAlt");

	ImGui::End();
}

template <typename T>  
std::vector<float> dae::GraphPlot::GetTimings(int samples) const  
{  
   T* arr = new T[ARR_SIZE]{};  
   std::vector<float> elapsedTimes;  
   std::vector<std::vector<float>> allTimings(TOTAL_STEPS, std::vector<float>(samples));  

   for (int sample = 0; sample < samples; ++sample) {  
       for (int stepsize = 1, index = 0; stepsize <= MAX_STEPSIZE; stepsize *= 2, ++index) {  
           auto start = high_resolution_clock::now();  

           if constexpr (std::is_same_v<T, int>) {  
               for (int i = 0; i < ARR_SIZE; i += stepsize) arr[i] *= 2;  
           } else if constexpr (std::is_same_v<T, GameObject3D>) {  
               for (int i = 0; i < ARR_SIZE; i += stepsize) arr[i].id *= 2;  
           } else if constexpr (std::is_same_v<T, GameObject3DAlt>) {  
               for (int i = 0; i < ARR_SIZE; i += stepsize) arr[i].id *= 2;  
           }  

           auto end = high_resolution_clock::now();  
           float elapsedTime = static_cast<float>(duration_cast<microseconds>(end - start).count());  
           allTimings[index][sample] = elapsedTime;  
       }  
   }  

   for (const auto& timings : allTimings) {  
       std::vector<float> sortedTimings = timings;  
       std::sort(sortedTimings.begin(), sortedTimings.end());  
       elapsedTimes.push_back(sortedTimings[sortedTimings.size() / 2]);  
   }  

   delete[] arr;  
   return elapsedTimes;  
}
