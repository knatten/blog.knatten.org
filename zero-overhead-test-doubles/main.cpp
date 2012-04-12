#include <cstddef>

bool simulate_more = true;
void doStuffWith(double[]);

namespace example1 {

    //snippetysnip_begin:example1-modelsim
    class Model {
    public:
        double getValue(size_t i);
        size_t size();
    };

    class Simulator {
        Model* model;
    public:
        Simulator() : model(new Model()) {}

        void inner_loop() {
            double values[model->size()];
            while (simulate_more) {
                for (size_t i = 0; i < model->size(); ++i) {
                    values[i] = model->getValue(i);
                }
                doStuffWith(values);
            }
        }
    };
    //snippetysnip_end

    //snippetysnip_begin:example1-production
    void production() {
        Simulator sim;
    }
    //snippetysnip_end

}

namespace example2 {

    //snippetysnip_begin:example2-modelsim
    class Model {
    public:
        virtual double getValue(size_t i); //<--- virtual
        virtual size_t size();
    };

    class Simulator {
        Model* model;
    public:
        Simulator(Model* model) : model(model) {} //<--- inject dependency on Model

        void inner_loop() {
            double values[model->size()];
            while (simulate_more) {
                for (size_t i = 0; i < model->size(); ++i) {
                    values[i] = model->getValue(i);
                }
                doStuffWith(values);
            }
        }
    };
    //snippetysnip_end

    //snippetysnip_begin:example2-test
    class FakeModel : public Model {
    public:
        virtual double getValue(size_t i);
        virtual size_t size();
    };

    void test_inner_loop() {
        FakeModel fakeModel;
        Simulator simulator(&fakeModel);
        //Do test
    }
    //snippetysnip_end

    //snippetysnip_begin:example2-production
    void production() {
        Model model; //<--- instantiated outside of Simulator
        Simulator sim(&model);
    }
    //snippetysnip_end

    double Model::getValue(size_t i) { return .0; }
    size_t Model::size() { return 0; }
    double FakeModel::getValue(size_t i) { return .0; }
    size_t FakeModel::size() { return 0; }
}



namespace example3 {

    //snippetysnip_begin:example3-modelsim
    class Model {
    public:
        double getValue(size_t i); //<--- look mom, no virtual!
        size_t size();
    };

    template <class ModelT> //<--- type of model as a template parameter
    class Simulator {
        ModelT* model;
    public:
        Simulator(ModelT* model) : model(model) {} //<--- Model is still injected

        void inner_loop() {
            double values[model->size()];
            while (simulate_more) {
                for (size_t i = 0; i < model->size(); ++i) {
                    values[i] = model->getValue(i);
                }
                doStuffWith(values);
            }
        }
    };
    //snippetysnip_end

    //snippetysnip_begin:example3-test
    class FakeModel { //<--- doesn't need to inherit from Model, only implement the methods used in inner_loop()  
        double getValue(size_t i);
        size_t size();
    };

    void test_inner_loop() {
        FakeModel fakeModel; 
        Simulator<FakeModel> simulator(&fakeModel);
        //Do test
    }
    //snippetysnip_end

    //snippetysnip_begin:example3-production
    void production() {
        Model model; //<--- still instantiated outside of Simulator
        Simulator<Model> sim(&model);
    }
    //snippetysnip_end

    double Model::getValue(size_t i) { return .0; }
    double FakeModel::getValue(size_t i) { return .0; }
}

int main() {
}
