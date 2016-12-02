#pragma once
#include <cstddef>
#include <vector>
#include <string>
#include <memory>

#include "activation_functor.h"
#include "type.hpp"

namespace Hippocrates::Phenotype {

class NeuralNetwork;
class Neuron {
	friend NeuralNetwork;
public:
	struct Connection {
		Neuron* neuron = nullptr;
		Type::connection_weight_t weight = 0.0f;
		bool isRecursive = false;
		bool outGoing = false;
	};
private:
	std::vector<Connection> connections;
	Type::neuron_value_t lastActionPotential = 0.0f;
	std::size_t layer = 0U;
    std::unique_ptr<const IActivationFunctor> activationFunctor = GetActivationFunctorUsed();

public:
	Neuron() = default;
	explicit Neuron(std::vector<Connection> connections);
	Neuron(const Neuron& other) = default;
	Neuron(Neuron&& other) = default;
	explicit Neuron(const std::string& json);
	~Neuron() = default;

	auto operator=(const Neuron& other)&-> Neuron& = default;
	auto operator=(Neuron&& other)& -> Neuron& = default;

	auto SetInput(Type::neuron_value_t input) -> void;
	auto GetConnections() const -> const std::vector<Connection>& { return connections; }
	auto RequestDataAndGetActionPotential() ->Type::neuron_value_t;
	auto GetLayer() const -> std::size_t { return layer; }
	auto GetJSON() const->std::string;

	auto Reset() -> void;

private:
	static auto GetActivationFunctorUsed() -> std::unique_ptr<IActivationFunctor>;
	auto AddConnection(Connection connection) -> void;
};

}
