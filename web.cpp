#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "World.h"
#include "Org.h"

emp::web::Document doc{"target"};

class EcoAnimator : public emp::web::Animate {

private:
    static constexpr int RECT_SIDE = 10;
    static constexpr int num_w_boxes = 20;
    static constexpr int num_h_boxes = 20;

    emp::web::Canvas canvas;
    emp::Random random{5};
    OrgWorld world{random};

public:
    EcoAnimator() 
      : canvas(RECT_SIDE * num_w_boxes, RECT_SIDE * num_h_boxes, "canvas") 
    {
        world.Resize(num_w_boxes, num_h_boxes);
        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);

        for (int i = 0; i < 2; i++) {
            world.Inject(Organism(&random, i));
        }

        // Insert canvas into webpage and add control buttons
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");
    }

    void DoFrame() override {
        world.Update();
        Draw();
    }

    void Draw() {
        canvas.Clear(); 
        int org_num = 0;
        for (int x = 0; x < num_w_boxes; x++) {
            for (int y = 0; y < num_h_boxes; y++) {
                if (world.IsOccupied(org_num)) {
                    auto& org = world.GetOrg(org_num);
                    if (org.GetSpecies() == 0) {
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "blue", "black");
                    } else {
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "red", "black");
                    }
                } else {
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "white", "black");
                }
                org_num++;
            }
        }
    }
};

EcoAnimator animator;

int main() {
    animator.Step();
}
