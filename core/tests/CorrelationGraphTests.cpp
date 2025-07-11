#include <gtest/gtest.h>
#include <grimoire/CorrelationGraph.hpp>
#include <grimoire/Diagnostics.hpp>

TEST(CorrelationGraphTests, RootCauseIsCorrect) {
    auto root = std::make_shared<Diagnostics>();
    root->reportError("Root");

    auto child = std::make_shared<Diagnostics>();
    child->chainTo(root->getId());
    child->reportWarning("Child");

    CorrelationGraph graph;
    graph.addNode(root);
    graph.addNode(child);

    auto rootCause = graph.getRootCause(child->getId());
    EXPECT_EQ(rootCause->getId(), root->getId());
}
